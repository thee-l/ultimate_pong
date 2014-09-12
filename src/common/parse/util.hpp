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
#include "../deserialize.h"
#include "json/json.h"
#include <tuple>
namespace pong { namespace parse
{
  // Forward declarations.
  template <class Type> struct Value;
  template <class... Types> struct Tuple;
  template <class Type> struct Object;

  template <class Type>
  struct find_parser
  {
    using type = std::conditional_t<std::is_fundamental<Type>::value,
                                    Value<Type>,
                                    Object<Type> >;
  };

  template <class... Types>
  struct find_parser<std::tuple<Types...> >
  {
    using type = Tuple<Types...>;
  };
} }