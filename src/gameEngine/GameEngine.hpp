#ifndef PINGPONG_SDL2_GAMEENGINE_H
#define PINGPONG_SDL2_GAMEENGINE_H

#include <SDL.h>
#include <iostream>

class GameEngine {
  bool init();

  void update();

  void handleKeyboardEvent(SDL_Event event);

  void handleMouseEvent(SDL_Event event);

  void logMessage(const std::string &message, bool isError = false);

  void loadScene();

  void updateGame();

  void renderGame();
};

#endif //PINGPONG_SDL2_GAMEENGINE_H
