#ifndef PINGPONG_SDL2_PLAYERSCORE_HPP
#define PINGPONG_SDL2_PLAYERSCORE_HPP

#include <SDL_render.h>
#include <SDL_ttf.h>
#include <cstdint>
#include "../utils/Vector2.hpp"
#include <optional>

enum PLAYER { ONE, TWO };

class PlayerScore {
  SDL_Rect playerOneRect{};
  SDL_Rect playerTwoRect{};
  SDL_Texture* playerOneTexture{};
  SDL_Texture* playerTwoTexture{};

 public:
  int playerOne{0};
  int playerTwo{0};
  SDL_Rect winnerRect{};
  SDL_Texture* winnerTexture{};
  SDL_TimerID winnerTimerID{};

  void init(int screenWidth, int screenHeight, TTF_Font* font, SDL_Color color,
            SDL_Renderer* renderer);

  void update(TTF_Font* font, SDL_Color color, SDL_Renderer* renderer);

  void render(SDL_Renderer* renderer);

  [[nodiscard]] std::optional<PLAYER> checkWinner() const;

  void resetScores();

  void free();
};

#endif  //PINGPONG_SDL2_PLAYERSCORE_HPP
