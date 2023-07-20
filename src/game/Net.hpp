#ifndef PINGPONG_SDL2_NET_HPP
#define PINGPONG_SDL2_NET_HPP
#include <SDL_rect.h>
#include <SDL_render.h>
#include <vector>
#include "../utils/Vector2.hpp"

class Net {
  SDL_FRect rect{};
  std::vector<float> yPositions;

 public:
  Net() = default;
  Net(int windowHeight, int windowWidth);
  void render(SDL_Renderer* renderer);
};

#endif  //PINGPONG_SDL2_NET_HPP
