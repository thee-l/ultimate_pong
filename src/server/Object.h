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
#include "core/common/volume.h"
#include "core/common/pif/helper.h"

namespace pong
{
  enum class PhysicsType
  {
    Undefined,
    Paddle,
    Ball
  };
  struct PaddleOptions
  {
    using vec_t = math::vector<double>;
    PaddleOptions(vec_t const& vec = vec_t()) noexcept : destination(vec) {}
    vec_t destination;

    DECLARE_FORMATTED_AS_OBJECT;

    DECLARE_PROPERTY_VALUES(1, "Destination");
    DECLARE_PROPERTIES_TUPLE(math::vector<double>);
    DECLARE_PROPERTIES(this->destination);
  };
  struct BallOptions
  {
    using vec_t = math::vector<double>;
    BallOptions(vec_t const& vec = vec_t()) noexcept : velocity(vec) {}
    vec_t velocity;

    DECLARE_FORMATTED_AS_OBJECT;

    DECLARE_PROPERTY_VALUES(1, "Velocity");
    DECLARE_PROPERTIES_TUPLE(math::vector<double>);
    DECLARE_PROPERTIES(this->velocity);
  };

  /*!
   * \brief A variant to encapsulate the differences of a paddle and a ball.
   *
   * Kind of works like the SDL_Event structure. This kind of thing is elegant
   * *enough*.
   */
  struct PhysicsOptions
  {
    /* implicit */ PhysicsOptions(PhysicsType type = PhysicsType::Undefined)
                                  : type(type)
    {
      switch(type)
      {
        case PhysicsType::Paddle:
        {
          this->paddle_options = PaddleOptions();
          break;
        }
        case PhysicsType::Ball:
        {
          this->ball_options = BallOptions();
          break;
        }
        default: break;
      }
    }

    PhysicsType type;
    union
    {
      PaddleOptions paddle_options;
      BallOptions ball_options;
    };
    VolumeSides constraints = VolumeSide::None;

    DECLARE_FORMATTED_WITH_CUSTOM_IMPL;
  };

  using id_type = uint16_t;
  struct Object
  {
    explicit Object(const Volume& vol = Volume{},
                    PhysicsOptions opts = {})
                    : volume(vol), physics_options(opts) {}

    Volume volume;
    PhysicsOptions physics_options;

    DECLARE_FORMATTED_AS_OBJECT;

    DECLARE_PROPERTY_VALUES(2, "Volume", "PhysicsOptions");
    DECLARE_PROPERTIES_TUPLE(Volume, PhysicsOptions);
    DECLARE_PROPERTIES(this->volume, this->physics_options);
  };

  inline Object make_paddle(const Volume& v) noexcept
  {
    return Object{v, PhysicsType::Paddle};
  }
  inline Object make_ball(const Volume& v) noexcept
  {
    return Object{v, PhysicsType::Ball};
  }

  inline bool isPaddle(const Object& obj) noexcept
  {
    return obj.physics_options.type == PhysicsType::Paddle;
  }
  inline bool isBall(const Object& obj) noexcept
  {
    return obj.physics_options.type == PhysicsType::Ball;
  }
}

BEGIN_FORMATTER_SCOPE
{
  DECLARE_FORMATTER(pong::PhysicsOptions);
}
END_FORMATTER_SCOPE
