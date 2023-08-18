#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <Engine.hpp>
#include "../utils/Constants.hpp"
#include "Timer.hpp"

bool Engine::init() {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    logMessage("Failed to init SDL", true);
    return false;
  }

  const int imgFlags = IMG_INIT_PNG;
  if ((IMG_Init(imgFlags) & imgFlags) != imgFlags) {
    logMessage("Failed to init IMG", true);
    return false;
  }

  if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
    logMessage("Warning: Linear texture filtering not enabled!");
  }

  window =
      SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
  if (!window) {
    logMessage("Failed to load window", true);
    return false;
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer) {
    logMessage("Failed to load renderer", true);
    return false;
  }

  if (TTF_Init() != 0) {
    logMessage("Failed to init TTF", true);
    return false;
  }

  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) != 0) {
    logMessage("Failed to init Mix Open Audio", true);
  }

  globalFont = TTF_OpenFont(
      (Constants::ASSETS_PATH + "fonts/PressStart2P-Regular.ttf").c_str(), 50);
  if (globalFont == nullptr) {
    logMessage("Global font not loaded", true);
  }

  return loadScene();
}

void Engine::update() {
  timer.start();

  SDL_Event event;
  while (SDL_PollEvent(&event) != 0) {
    if (event.type == SDL_QUIT) {
      isRunning = false;
      return;
    } else if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
      keyboardManager.handleEvent(event);
    }
  }
  if (!isStopped)
    updateGame(timer.deltaTime);
}

void Engine::render() {
  // Clear screen
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  if (!isStopped) {
    if (gameState.score.winnerTimerID) {
      SDL_RemoveTimer(gameState.score.winnerTimerID);
    }
    renderGame();
  } else {
    SDL_RenderCopy(renderer, gameState.score.winnerTexture, nullptr,
                   &gameState.score.winnerRect);
  }
  // Update screen
  SDL_RenderPresent(renderer);
  timer.updateDeltaTime();
}

void Engine::close() {
  // Close game & resources
  isRunning = false;
  gameState.free();
  // Then SDL resources
  Mix_FreeChunk(paddleHitSound);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  TTF_CloseFont(globalFont);
  renderer = nullptr;
  window = nullptr;
  globalFont = nullptr;
  TITLE = nullptr;
  paddleHitSound = nullptr;
  Mix_Quit();
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
}

void Engine::logMessage(const std::string& message, bool isError) {
  if (isError) {
    std::string msg = std::format("({}): {}", message, SDL_GetError());
    SDL_Log("%s", msg.c_str());
    return;
  }
  std::printf("%s\n", message.c_str());
}

bool Engine::loadScene() {
  paddleHitSound =
      Mix_LoadWAV((Constants::ASSETS_PATH + "PaddleHit.wav").c_str());
  if (paddleHitSound == nullptr) {
    logMessage("paddleHitSound not loaded", true);
    return false;
  }

  const auto p1Position =
      Vector2(50.0f, (WINDOW_HEIGHT / 2.0f) - (Player::HEIGHT / 2.0f));
  if (!gameState.playerOne.init(renderer, p1Position))
    return false;

  const auto p2Position =
      Vector2(WINDOW_WIDTH - Player::WIDTH - 50.0f,
              (WINDOW_HEIGHT / 2.0f) - (Player::HEIGHT / 2.0f));
  if (!gameState.playerTwo.init(renderer, p2Position))
    return false;

  const auto ballPosition = Vector2(WINDOW_WIDTH / 2.0f - Ball::WIDTH / 2.0f,
                                    WINDOW_HEIGHT / 2.0f - Ball::HEIGHT / 2.0f);
  if (!gameState.ball.init(renderer, ballPosition))
    return false;

  gameState.net = {WINDOW_HEIGHT, WINDOW_WIDTH};
  gameState.score.init(WINDOW_WIDTH, WINDOW_HEIGHT, globalFont,
                       defaultFontColor, renderer);
  return true;
}

void Engine::updateGame(float dt) {

  if (gameState.score.checkWinner() == PLAYER::ONE) {
    logMessage("Player one has won");
    showWinner(true);
    return;
  } else if (gameState.score.checkWinner() == PLAYER::TWO) {
    logMessage("Player two has won");
    showWinner(false);
    return;
  }

  if (keyboardManager.pressedKeys.contains(SDL_SCANCODE_UP)) {
    gameState.playerTwo.update(dt, Vector2(0.0f, -Player::SPEED));
  } else if (keyboardManager.pressedKeys.contains(SDL_SCANCODE_DOWN)) {
    gameState.playerTwo.update(dt, Vector2(0.0f, Player::SPEED));
  }
  if (keyboardManager.pressedKeys.contains(SDL_SCANCODE_W)) {
    gameState.playerOne.update(dt, Vector2(0.0f, -Player::SPEED));
  } else if (keyboardManager.pressedKeys.contains(SDL_SCANCODE_S)) {
    gameState.playerOne.update(dt, Vector2(0.0f, Player::SPEED));
  }

  SDL_FRect intersect;
  if (SDL_IntersectFRect(&gameState.ball.rect, &gameState.playerOne.rect,
                         &intersect)) {
    gameState.ball.update(
        dt, true, gameState.playerOne.checkPaddleHitSection(intersect.y));
    Mix_PlayChannel(-1, paddleHitSound, 0);
  } else if (SDL_IntersectFRect(&gameState.ball.rect, &gameState.playerTwo.rect,
                                &intersect)) {
    gameState.ball.update(
        dt, false, gameState.playerTwo.checkPaddleHitSection(intersect.y));
    Mix_PlayChannel(-1, paddleHitSound, 0);
  } else if (gameState.ball.position.x < -Ball::WIDTH) {
    gameState.score.playerTwo += 1;
    gameState.score.update(globalFont, defaultFontColor, renderer);
    gameState.ball.reset(false);
  } else if (gameState.ball.position.x > WINDOW_WIDTH + Ball::WIDTH) {
    gameState.score.playerOne += 1;
    gameState.score.update(globalFont, defaultFontColor, renderer);
    gameState.ball.reset(true);
  } else {
    gameState.ball.update(dt);
  }
}

void Engine::renderGame() {
  gameState.playerOne.render(renderer);
  gameState.playerTwo.render(renderer);
  gameState.ball.render(renderer);
  gameState.net.render(renderer);
  gameState.score.render(renderer);
}

void Engine::showWinner(bool isFirstPlayer) {
  isStopped = true;
  gameState.score.winnerTimerID =
      Timer::setTimeout(2000, [this]() -> void { isStopped = false; });
  SDL_Surface* surface = TTF_RenderText_Solid(
      globalFont, isFirstPlayer ? "Player One Won" : "Player Two Won!",
      defaultFontColor);
  gameState.score.winnerTexture =
      SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);
  surface = nullptr;
  gameState.score.resetScores();
  gameState.score.update(globalFont, defaultFontColor, renderer);
}
