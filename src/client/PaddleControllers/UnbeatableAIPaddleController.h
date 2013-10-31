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
#ifndef ULTIMATE_PONG_UNBEATABLE_AI_PADDLE_CONTROLLER_H
#define ULTIMATE_PONG_UNBEATABLE_AI_PADDLE_CONTROLLER_H
#include "PaddleController.hpp"
#include "Ball.h"
namespace pong
{
  class UnbeatableAIPaddleController : public PaddleController
  {
  public:
    UnbeatableAIPaddleController(Ball* tracked = nullptr) :
                                                         tracked_ball(tracked){}
    virtual void update(Paddle* paddle);

    /*!
     * \brief The ball which the paddle needs to be constantly on top of.
     *
     * A nullptr ball will be ignored making
     * UnbeatableAIPaddleController::update a no-op.
     */
    Ball* tracked_ball = nullptr;
  };
};
#endif