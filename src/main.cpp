#define SDL_MAIN_HANDLED

#include <SDL.h>
#include <SDL_ttf.h>
#include <fmt/format.h>
#include <iostream>
#include <vector>

// Game manager variables
const char *WINDOW_TITLE = "TicTacToe 2";
bool isRunning = true;
SDL_Window *window;
SDL_Renderer *renderer;
int screenWidth = 600;
int screenHeight = 600;
TTF_Font *globalFont;
SDL_Color defaultFontColor = {0, 0, 0};
SDL_Point mousePosition;

bool init();

void update();

void handleKeyboardEvent(SDL_Event event);

void handleMouseEvent(SDL_Event event);

void logMessage(const std::string &message, bool isError = false);

void loadScene();

void updateGame();

void renderGame();

bool init() {
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

void update() {
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

void render() {
  //Clear screen
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

  renderGame();

  //Update screen
  SDL_RenderPresent(renderer);
}

void close() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  TTF_CloseFont(globalFont);
  renderer = nullptr;
  window = nullptr;
  globalFont = nullptr;
  TTF_Quit();
  SDL_Quit();
}

void handleKeyboardEvent(SDL_Event event) {
}

void handleMouseEvent(SDL_Event event) {
  mousePosition = {.x = event.button.x, .y = event.button.y};
}

void logMessage(const std::string &message, bool isError) {
  if (isError) {
    std::string msg = fmt::format("{} : {}", message, SDL_GetError());
    SDL_Log("%s", msg.c_str());
    return;
  }
  std::printf("%s\n", message.c_str());
}

void loadScene() {

}

void updateGame() {

}

void renderGame() {
}

int main() {
  if (!init()) return 1;

  while (isRunning) {
    update();
    render();
  }

  close();

  return 0;
}
