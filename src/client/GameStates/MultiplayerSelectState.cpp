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
#include "MultiplayerSelectState.h"
#include "common/center.hpp"
#include "../widgets/helper.h"
namespace pong
{
  MultiplayerSelectState::
  MultiplayerSelectState(Game& g, std::shared_ptr<GameState> rs) noexcept
                                                 : g_(g),
                                                   back_(back_button(g, rs))
  {
    Volume vol;
    vol.width = 650;
    vol.height = 150;
    vol.pos.x = center(0, g.settings.extent.x, vol.width);
    vol.pos.y = center(0, g.settings.extent.y, vol.height);
    this->addr_input_.volume(vol);

    this->addr_input_.font_renderer(g.settings.font.get());
  }
  void MultiplayerSelectState::update() noexcept {}

  void MultiplayerSelectState::
  handleEvent(const SDL_Event& event) noexcept
  {
    if(event.type == SDL_QUIT) this->g_.exiting = true;
    this->addr_input_.handle_event(event);
  }

  void MultiplayerSelectState::
  render(SDL_Renderer* renderer) const noexcept
  {
    this->addr_input_.render(renderer);
  }
}
