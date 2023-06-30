#include <Engine.hpp>
#include <SDL.h>
#include <SDL_ttf.h>
#include <fmt/format.h>
#include <vector>

bool Engine::init() {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    logMessage("Failed to init SDL", true);
    return false;
  }

  //Get device display mode
  //  SDL_DisplayMode displayMode;
  //  if (SDL_GetCurrentDisplayMode(0, &displayMode) == 0) {
  //    screenWidth = displayMode.w;
  //    screenHeight = displayMode.h;
  //  }

  if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
    logMessage("Warning: Linear texture filtering not enabled!");
  }

  window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight,
                            SDL_WINDOW_SHOWN);
  if (!window) {
    logMessage("Failed to load window", true);
    return false;
  }
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (!renderer) {
    logMessage("Failed to load renderer", true);
    return false;
  }
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

  if (TTF_Init() != 0) {
    logMessage("Failed to init TTF", true);
    return false;
  }
  globalFont = TTF_OpenFont("assets/fonts/Roboto-Regular.ttf", 100);

  loadScene();
  return true;
}

void Engine::update() {
  SDL_Event event;
  while (SDL_PollEvent(&event) != 0) {
    if (event.type == SDL_QUIT) {
      isRunning = false;
      return;
    } else if (event.type == SDL_KEYDOWN) {
      handleKeyboardEvent(event);
    } else if (event.type == SDL_MOUSEBUTTONDOWN) {
      handleMouseEvent(event);
      updateGame();
    }
  }
}

void Engine::render() {
  //Clear screen
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

  renderGame();

  //Update screen
  SDL_RenderPresent(renderer);
}

void Engine::close() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  TTF_CloseFont(globalFont);
  renderer = nullptr;
  window = nullptr;
  globalFont = nullptr;
  TTF_Quit();
  SDL_Quit();
}

void Engine::handleKeyboardEvent(SDL_Event event) {
}

void Engine::handleMouseEvent(SDL_Event event) {
  mousePosition = {.x = event.button.x, .y = event.button.y};
}

void Engine::logMessage(const std::string &message, bool isError) {
  if (isError) {
    std::string msg = fmt::format("{} : {}", message, SDL_GetError());
    SDL_Log("%s", msg.c_str());
    return;
  }
  std::printf("%s\n", message.c_str());
}

void Engine::loadScene() {

}

void Engine::updateGame() {

}

void Engine::renderGame() {
}
