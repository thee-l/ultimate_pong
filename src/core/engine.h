/* * PpM - Pong Plus More - A pong clone full of surprises written with C++11.
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
#pragma once
#include "SDL.h"

#include "json/json.h"

#include "io/Logger.h"

#include "plugin/plugins.h"
#include "plugin/Req_Dispatcher.h"

namespace engine
{
  struct State
  {
    bool running = true;
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
  };

  inline void step(State& state) noexcept {}

  pong::Json_Plugin spawn_plugin(Json::Value const& json) noexcept;

  void add_core_methods(pong::Req_Dispatcher& dispatch, State& state,
                        pong::Logger& log);
}