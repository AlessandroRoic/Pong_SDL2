#ifndef PINGPONG_SDL2_DELTATIMER_HPP
#define PINGPONG_SDL2_DELTATIMER_HPP

#include <chrono>
#include <cstdint>

class DeltaTimer {
  std::chrono::time_point<std::chrono::steady_clock> startTime;

 public:
  float deltaTime;
  DeltaTimer() : deltaTime{0.0f} {}
  void start();
  void updateDeltaTime();
};
#endif  //PINGPONG_SDL2_DELTATIMER_HPP
