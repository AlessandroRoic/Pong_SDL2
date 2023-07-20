#ifndef PINGPONG_SDL2_GAMEENGINE_H
#define PINGPONG_SDL2_GAMEENGINE_H

#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include "../game/GameState.hpp"
#include "DeltaTimer.hpp"
#include "GameState.hpp"
#include "KeyboardManager.hpp"
#include "Window.hpp"

class Engine {
  const char* TITLE = "Pong";
  SDL_Window* window{};
  SDL_Renderer* renderer{};
  TTF_Font* globalFont{};
  SDL_Color defaultFontColor = {255, 255, 255};
  KeyboardManager keyboardManager;
  GameState gameState;
  DeltaTimer timer;

  void updateGame(float dt);
  void renderGame();
  void showWinner(bool isFirstPlayer);
  bool loadScene();

 public:
  static const int WINDOW_WIDTH = 1000;
  static const int WINDOW_HEIGHT = 600;
  bool isRunning = true;
  bool isStopped = false;
  Mix_Chunk* paddleHitSound{};

  bool init();
  void update();
  void render();
  void close();
  static void logMessage(const std::string& message, bool isError = false);
};

#endif  // PINGPONG_SDL2_GAMEENGINE_H
