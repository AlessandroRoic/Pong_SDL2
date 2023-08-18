#include "PlayerScore.hpp"
#include <SDL_ttf.h>
#include "Engine.hpp"

constexpr int WINNER_TEXT_WIDTH = 300;
constexpr int WINNER_TEXT_HEIGHT = 130;

void PlayerScore::init(const int screenWidth, const int screenHeight,
                       TTF_Font* font, const SDL_Color color,
                       SDL_Renderer* renderer) {
  winnerRect = {screenWidth / 2 - WINNER_TEXT_WIDTH / 2,
                screenHeight / 2 - WINNER_TEXT_HEIGHT / 2, WINNER_TEXT_WIDTH,
                WINNER_TEXT_HEIGHT};
  playerOneRect = {screenWidth / 4, 20};
  playerTwoRect = {3 * screenWidth / 4, 20};
  update(font, color, renderer);
}

void PlayerScore::update(TTF_Font* font, const SDL_Color color,
                         SDL_Renderer* renderer) {
  SDL_Surface* surface =
      TTF_RenderText_Solid(font, std::to_string(playerOne).c_str(), color);
  playerOneTexture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);
  surface = nullptr;

  SDL_Surface* surfaceTwo =
      TTF_RenderText_Solid(font, std::to_string(playerTwo).c_str(), color);
  playerTwoTexture = SDL_CreateTextureFromSurface(renderer, surfaceTwo);
  surfaceTwo = nullptr;

  SDL_QueryTexture(playerOneTexture, nullptr, nullptr, &playerOneRect.w,
                   &playerOneRect.h);
  SDL_QueryTexture(playerTwoTexture, nullptr, nullptr, &playerTwoRect.w,
                   &playerTwoRect.h);
}

void PlayerScore::render(SDL_Renderer* renderer) {
  SDL_RenderCopy(renderer, playerOneTexture, nullptr, &playerOneRect);
  SDL_RenderCopy(renderer, playerTwoTexture, nullptr, &playerTwoRect);
}

void PlayerScore::free() {
  SDL_DestroyTexture(playerOneTexture);
  SDL_DestroyTexture(playerTwoTexture);
  SDL_DestroyTexture(winnerTexture);
  playerOneTexture = nullptr;
  playerTwoTexture = nullptr;
  winnerTexture = nullptr;
}

std::optional<PLAYER>  PlayerScore::checkWinner() const {
  if (playerOne == 11) {
    return PLAYER::ONE;
  } else if (playerTwo == 11) {
    return PLAYER::TWO;
  }
  return std::nullopt;
}

void PlayerScore::resetScores() {
  playerOne = 0;
  playerTwo = 0;
}
