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
#pragma once

#include <string>
#include <vector>
#include <deque>
#include <functional>
#include <utility>

#include "core/io/Logger.h"
#include "core/plugin/req.h"
#include "core/plugin/response.h"

namespace client
{
  struct Client
  {
    using cb_t = std::function<void(pong::Response const&)>;

    bool poll_request(pong::Request& req) noexcept;

    void post_request(pong::Request const& req) noexcept;
    void post_request(pong::Request const& req, cb_t callback) noexcept;

    void step() noexcept;
  private:
    std::deque<pong::Request> reqs_;
    std::vector<std::pair<pong::req_id_t, cb_t> > cbs_;
  };

  namespace detail
  {
    template <class Type>
    void make_params_impl(Json::Value& val, Type const& t)
    {
      val.append(FORMATTER_TYPE(Type)::dump(t));
    }
    template <class Type, class... Types>
    void make_params_impl(Json::Value& val, Type const& t1, Types&&... params)
    {
      // Append the first one first,
      make_params_impl(val, t1);
      // Then the others.
      make_params_impl(val, std::forward<Types>(params)...);
    }
  }
  template <class... Types>
  Json::Value make_params(Types&&... params)
  {
    Json::Value val(Json::ValueType::arrayValue);;
    detail::make_params_impl(val, std::forward<Types>(params)...);
    return val;
  }

  void log_message(Client&, pong::Severity, std::string const&) noexcept;
}
