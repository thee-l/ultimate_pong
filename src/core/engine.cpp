/*
 * PpM - Pong Plus More - A pong clone full of surprises written with C++11.
 * Copyright (C) 2013  Luke San Antonio
 *
 * You can contact me (Luke San Antonio) at lukesanantonio@gmail.com!
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <iostream>
#include <memory>
#include <fstream>
#include <uv.h>
#include "SDL.h"
#include "json/json.h"

#include "core/plugin/plugins.h"
#include "core/io/Logger.h"

#include "core/plugin/Req_Dispatcher.h"

pong::Json_Plugin spawn_plugin(Json::Value const& json) noexcept
{
  std::vector<char*> args;

  for(Json::Value const& array_element : json["plugin"])
  {
    args.push_back((char*) array_element.asCString());
  }
  args.push_back(NULL);

  pong::ipc::Spawn_Options opts;
  opts.args = &args[0];
  opts.cwd = NULL;
  return pong::make_json_plugin<pong::Child_Process>(opts);
}

struct State
{
  bool running = true;
  SDL_Window* window = nullptr;
  SDL_Renderer* renderer = nullptr;
};

void step(State& state) noexcept
{

}

int main(int argc, char** argv)
{
  if(argc < 2)
  {
    std::cerr << "usage: " << argv[0] << " <game-decl>" << std::endl;
    return EXIT_FAILURE;
  }

  Json::Reader read(Json::Features::strictMode());
  std::ifstream file(argv[1]);

  Json::Value json;
  read.parse(file, json);

  using pong::Logger; using pong::Logger_Stream; using pong::Severity;
  Logger log(Logger_Stream::Err);

  std::string cwd = json.get("cwd", "").asString();
  if(cwd.size())
  {
    log.log(Severity::Info, "Changing directory: '" + cwd + "'");
    uv_chdir(json.get("cwd", "").asString().c_str());
  }

  // Spawn the main plugin.
  if(!json.isMember("plugin"))
  {
    log.log(Severity::Error, "No mod specified in game decl spec");
    return EXIT_FAILURE;
  }

  log.log(Severity::Info, "Spawning mod: " + json["plugin"][0].asString());
  pong::Json_Plugin plugin = spawn_plugin(json);

  State state;
  pong::Req_Dispatcher dispatch;

  // Populate the dispatcher!

  dispatch.add_method<pong::Severity, std::string>("Core.Log",
  [&log](pong::Severity s, std::string msg)
  {
    log.log(s, "(Plugin) " + msg);
    return pong::Response{0, Json::Value(true)};
  });

  while(state.running)
  {
    pong::Request req;
    while(plugin.poll_request(req))
    {
      pong::Response res = dispatch.dispatch(req);

      // Null out the id if necessary.
      if(!res.id && is_error_response(res)) res.id = pong::null_t{};

      // If the requester wanted a response give them one. Also send a respons
      // if there is an error.
      else if(res.id)
      {
        plugin.post_response(res);
      }

      return true;
    }

    step(state);
  }

  return 0;
}
