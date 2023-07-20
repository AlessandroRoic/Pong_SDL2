#include "GameState.hpp"

void GameState::free() {
  playerOne.free();
  playerTwo.free();
  ball.free();
  score.free();
}
