#include "Ball.hpp"
#include <SDL_image.h>
#include <SDL_render.h>
#include <random>
#include "../engine/Engine.hpp"
#include "../utils/Constants.hpp"

constexpr float MIN_Y = -1.0f;
constexpr float MAX_Y = 1.0f;

enum DIRECTION { LEFT = -1, RIGHT = 1 };

void setRandomDirection(Vector2& velocity, DIRECTION direction) {
  std::random_device rd;
  std::mt19937 generator(rd());
  std::uniform_real_distribution<float> distribution(MIN_Y, MAX_Y);
  velocity = Vector2::normalize(Vector2(direction, distribution(generator)));
}

bool Ball::init(SDL_Renderer* renderer, Vector2 pos) {
  texture =
      IMG_LoadTexture(renderer, (Constants::ASSETS_PATH + "ball.png").c_str());
  if (texture == nullptr) {
    Engine::logMessage("Ball texture not loaded", true);
    return false;
  }
  position = pos;
  rect = {position.x, position.y, WIDTH, HEIGHT};
  wallHitSound = Mix_LoadWAV((Constants::ASSETS_PATH + "WallHit.wav").c_str());
  setRandomDirection(velocity, DIRECTION::RIGHT);
  return true;
}

void Ball::update(float dt) {
  position += (velocity * dt * currentSpeed);
  if (position.y < 0.0f) {
    position.y = 0.0f;
    velocity.y = -velocity.y;
    position += (velocity * dt * currentSpeed);
    Mix_PlayChannel(-1, wallHitSound, 0);
  } else if (position.y > Engine::WINDOW_HEIGHT - HEIGHT) {
    position.y = Engine::WINDOW_HEIGHT - HEIGHT;
    velocity.y = -velocity.y;
    position += (velocity * dt * currentSpeed);
    Mix_PlayChannel(-1, wallHitSound, 0);
  }
  rect.x = position.x;
  rect.y = position.y;
}

void Ball::update(float dt, bool firstPlayer, PADDLE_SECTION section) {
  const DIRECTION direction = firstPlayer ? DIRECTION::RIGHT : DIRECTION::LEFT;
  if (section == PADDLE_SECTION::TOP) {
    velocity = Vector2::normalize(Vector2(direction, 1));
  } else if (section == PADDLE_SECTION::MIDDLE) {
    velocity = Vector2::normalize(Vector2(direction, 0));
  } else if (section == PADDLE_SECTION::BOTTOM) {
    velocity = Vector2::normalize(Vector2(direction, -1));
  }
  currentSpeed = PADDLE_HIT_SPEED;
  update(dt);
}

void Ball::render(SDL_Renderer* renderer) {
  SDL_RenderCopyF(renderer, texture, nullptr, &rect);
}

void Ball::free() {
  Mix_FreeChunk(wallHitSound);
  SDL_DestroyTexture(texture);
  texture = nullptr;
  wallHitSound = nullptr;
}

void Ball::reset(bool hasFirstPlayerWon) {
  position = Vector2(Engine::WINDOW_WIDTH / 2.0f - Ball::WIDTH / 2.0f,
                     Engine::WINDOW_HEIGHT / 2.0f - Ball::HEIGHT / 2.0f);
  setRandomDirection(velocity,
                     hasFirstPlayerWon ? DIRECTION::RIGHT : DIRECTION::LEFT);
  rect.x = position.x;
  rect.y = position.y;
  currentSpeed = SPEED;
}

Ball::Ball() = default;
