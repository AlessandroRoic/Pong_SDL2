#ifndef PINGPONG_SDL2_TIMER_HPP
#define PINGPONG_SDL2_TIMER_HPP
#include <SDL_timer.h>
#include <functional>

class Timer {
 public:
  static SDL_TimerID setTimeout(Uint32 delay, std::function<void()> callback);
};

#endif  //PINGPONG_SDL2_TIMER_HPP
