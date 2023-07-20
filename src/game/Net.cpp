#include "Net.hpp"

constexpr int HEIGHT = 10;
constexpr int WIDTH = 5;
const int PADDING = HEIGHT + 10;

Net::Net(const int windowHeight, const int windowWidth) {
  const auto middle = static_cast<float>(windowWidth) / 2;
  rect = {middle, 0, WIDTH, HEIGHT};
  for (int i{5}; i < windowHeight + PADDING; i += PADDING) {
    yPositions.push_back(static_cast<float>(i));
  }
}

void Net::render(SDL_Renderer* renderer) {
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  for (auto i : yPositions) {
    rect.y = i;
    SDL_RenderFillRectF(renderer, &rect);
  }
}
