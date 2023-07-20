#include "Player.hpp"
#include <SDL_image.h>
#include <SDL_render.h>
#include "../engine/Engine.hpp"
#include "../utils/Constants.hpp"

template <typename T>
bool isInRange(const T& value, const T& low, const T& high) {
  return value >= low && (value < high);
}

bool Player::init(SDL_Renderer* renderer, Vector2 pos) {
  texture = IMG_LoadTexture(renderer,
                            (Constants::ASSETS_PATH + "player.png").c_str());
  if (texture == nullptr) {
    Engine::logMessage("Player texture not loaded", true);
    return false;
  }
  position = pos;
  rect = {position.x, position.y, WIDTH, HEIGHT};
  return true;
}

void Player::update(float dt, Vector2 velocity) {
  position += (velocity * dt);
  if (position.y < 0.0f) {
    position.y = 0.0f;
  } else if (position.y > (Engine::WINDOW_HEIGHT - HEIGHT)) {
    position.y = Engine::WINDOW_HEIGHT - HEIGHT;
  }
  rect.y = position.y;
}

void Player::render(SDL_Renderer* renderer) {
  SDL_RenderCopyF(renderer, texture, nullptr, &rect);
}

void Player::free() {
  SDL_DestroyTexture(texture);
  texture = nullptr;
}

PADDLE_SECTION Player::checkPaddleHitSection(float y) const {
  if (isInRange(y, rect.y, rect.y + HEIGHT / 3.0f)) {
    return TOP;
  } else if (isInRange(y, rect.y + HEIGHT / 3.0f + 1,
                       rect.y + HEIGHT * 2.0f / 3)) {
    return MIDDLE;
  } else if (isInRange(y, rect.y + HEIGHT * 2.0f / 3 + 1, rect.y + HEIGHT)) {
    return BOTTOM;
  }
}

Player::Player() = default;
