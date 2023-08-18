#include "DeltaTimer.hpp"

void DeltaTimer::start() {
  startTime = std::chrono::high_resolution_clock::now();
}

void DeltaTimer::updateDeltaTime() {
  auto stopTime = std::chrono::high_resolution_clock::now();
  deltaTime = std::chrono::duration<float, std::chrono::milliseconds::period>(
                  stopTime - startTime)
                  .count();
}
