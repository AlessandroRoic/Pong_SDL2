#define SDL_MAIN_HANDLED

#include "engine/Engine.hpp"

int main() {
  Engine gameEngine;
  if (!gameEngine.init())
    return 1;

  while (gameEngine.isRunning) {
    gameEngine.update();
    gameEngine.render();
  }

  gameEngine.close();

  return 0;
}
