/*
 * uGlue - Glue many languages together into a whole with ukernel-inspired RPC.
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
#include "req.h"
namespace pong
{
  struct Is_Null_Visitor : public boost::static_visitor<bool>
  {
    bool operator()(null_t) const noexcept
    {
      return true;
    }
    template <typename T>
    bool operator()(T const&) const noexcept
    {
      return false;
    }
  };

  bool is_null(req_id_t const& id) noexcept
  {
    return boost::apply_visitor(Is_Null_Visitor(), id);
  }
  bool is_null(optional_id_t const& id) noexcept
  {
    if(id) return is_null(id.value());
    return false;
  }

  struct Json_Id_Visitor : public boost::static_visitor<Json::Value>
  {
    template <typename Type>
    Json::Value operator()(Type const& t) const noexcept
    {
      return FORMATTER_TYPE(Type)::dump(t);
    }
  };
}
BEGIN_FORMATTER_SCOPE
{
  DEFINE_PARSER(pong::null_t, json)
  {
    return pong::null_t{};
  }
  DEFINE_DUMPER(pong::null_t, n)
  {
    return Json::ValueType::nullValue;
  }

  DEFINE_PARSER(pong::req_id_t, json)
  {
    pong::req_id_t id;

    if(json.isString())
    {
      id = json.asString();
    }
    else if(json.isIntegral())
    {
      id = json.asInt();
    }
    else if(json.isNull())
    {
      id = pong::null_t{};
    }
    else
    {
      throw pong::Invalid_Id_Exception{};
    }

    return id;
  }
  DEFINE_DUMPER(pong::req_id_t, id)
  {
    Json::Value val = boost::apply_visitor(pong::Json_Id_Visitor(), id);
    return val;
  }
  DEFINE_PARSER(pong::Request, js)
  {
    pong::Request req;

    // Only if there is an id, none is okay too.
    if(js.isMember("id"))
    {
      try
      {
        req.id = FORMATTER_TYPE(pong::req_id_t)::parse(js["id"]);
      }
      catch(pong::Invalid_Id_Exception& e)
      {
        // This means there is a bad id value, maybe it's floating point for
        // instance.
        throw pong::Invalid_Request_Exception{};
      }
    }

    // We need a method!
    if(!js.get("method", 0).isString())
    {
      throw pong::Invalid_Request_Exception{req.id};
    }
    req.method = js["method"].asString();

    if(js.isMember("params"))
    {
      req.params = js["params"];
    }

    return req;
  }
  DEFINE_DUMPER(pong::Request, req)
  {
    Json::Value json;

    // Only output an id if there is one.
    if(req.id)
    {
      json["id"] = FORMATTER_TYPE(pong::req_id_t)::dump(req.id.value());
    }

    json["method"] = req.method;

    if(req.params)
    {
      json["params"] = req.params.value();
    }

    return json;
  }
}
END_FORMATTER_SCOPE
