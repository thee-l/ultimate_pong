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
#include "common/Volume.h"
#include "util.h"
namespace pong
{
  struct Object
  {
    virtual ~Object() noexcept = 0;

    Object(const id_type id, const Volume& vol = Volume{})
           : id_(id), vol_(vol) {}

    id_type id() const noexcept { return this->id_; }

    const Volume& getVolume() const noexcept { return this->vol_; }
    Volume& getVolume() noexcept { return this->vol_; }

  private:
    const id_type id_;
    Volume vol_;
  };

  Object::~Object() {}
}
