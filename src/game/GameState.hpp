#ifndef PINGPONG_SDL2_GAMESTATE_HPP
#define PINGPONG_SDL2_GAMESTATE_HPP

#include <cstdint>
#include "Ball.hpp"
#include "Net.hpp"
#include "Player.hpp"
#include "PlayerScore.hpp"

class GameState {
 public:
  Player playerOne;
  Player playerTwo;
  PlayerScore score;
  Ball ball;
  Net net;

  void free();
};

#endif  // PINGPONG_SDL2_GAMESTATE_HPP
