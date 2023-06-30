#ifndef PINGPONG_SDL2_GAMEENGINE_H
#define PINGPONG_SDL2_GAMEENGINE_H

#include <SDL.h>
#include <iostream>
#include <SDL_ttf.h>

class Engine {
  const char *WINDOW_TITLE = "Pong";
  SDL_Window *window{};
  SDL_Renderer *renderer{};
  const int screenWidth = 600;
  const int screenHeight = 600;
  TTF_Font *globalFont{};
  SDL_Color defaultFontColor = {0, 0, 0};
  SDL_Point mousePosition{};

  void loadScene();

  void updateGame();

  void renderGame();

  void handleKeyboardEvent(SDL_Event event);

  void handleMouseEvent(SDL_Event event);

  void logMessage(const std::string &message, bool isError = false);

public:
  bool init();

  bool isRunning = true;

  void update();

  void render();

  void close();
};

#endif //PINGPONG_SDL2_GAMEENGINE_H
