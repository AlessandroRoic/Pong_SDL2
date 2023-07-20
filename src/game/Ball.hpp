#ifndef PINGPONG_SDL2_BALL_HPP
#define PINGPONG_SDL2_BALL_HPP

#include <SDL_mixer.h>
#include <SDL_rect.h>
#include <SDL_render.h>
#include "../utils/Vector2.hpp"
#include "Player.hpp"
class Ball {
  Vector2 velocity{};
  SDL_Texture* texture{};
  float currentSpeed{SPEED};
  static constexpr float SPEED{0.4f};
  static constexpr float PADDLE_HIT_SPEED{0.8f};

 public:
  static constexpr int HEIGHT{24};
  static constexpr int WIDTH{24};
  Vector2 position{};
  SDL_FRect rect{};
  Mix_Chunk* wallHitSound{};

  Ball();

  bool init(SDL_Renderer* renderer, Vector2 pos);

  void update(float dt);

  void update(float dt, bool firstPlayer, PADDLE_SECTION section);

  void render(SDL_Renderer* renderer);

  void reset(bool hasFirstPlayerWon);

  void free();
};

#endif  //PINGPONG_SDL2_BALL_HPP
