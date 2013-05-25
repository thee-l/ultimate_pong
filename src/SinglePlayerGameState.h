#ifndef ULTIMATE_PONG_SINGLE_PLAYER_GAME_STATE_H
#define ULTIMATE_PONG_SINGLE_PLAYER_GAME_STATE_H
#include "GameState.h"
#include "Paddle.h"
namespace pong
{
  class SinglePlayerGameState : public GameState
  {
  public:
    SinglePlayerGameState();
    SinglePlayerGameState(const SinglePlayerGameState&) = delete;
    SinglePlayerGameState(SinglePlayerGameState&&) = delete;
    SinglePlayerGameState& operator=(const SinglePlayerGameState&) = delete;
    SinglePlayerGameState& operator=(SinglePlayerGameState&&) = delete;
    virtual ~SinglePlayerGameState() = default;
  private:
    virtual void update_private() override {}
    virtual void render_private(SDL_Surface*) const override {}
  };
};
#endif