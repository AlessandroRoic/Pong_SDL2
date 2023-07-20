#ifndef PINGPONG_SDL2_PLAYER_HPP
#define PINGPONG_SDL2_PLAYER_HPP

#include <SDL_rect.h>
#include <SDL_render.h>
#include "../utils/Vector2.hpp"

enum PADDLE_SECTION{
  TOP,
  MIDDLE,
  BOTTOM
};

class Player {
  SDL_Texture* texture{};

 public:
  static constexpr int HEIGHT{70};
  static constexpr int WIDTH{10};
  static constexpr float SPEED{0.8};
  Vector2 position{};
  SDL_FRect rect{};

  Player();

  bool init(SDL_Renderer* renderer, Vector2 pos);

  void update(float dt, Vector2 velocity);

  void render(SDL_Renderer* renderer);

  void free();

  [[nodiscard]] PADDLE_SECTION checkPaddleHitSection(float y) const;
};

#endif  // PINGPONG_SDL2_PLAYER_HPP
