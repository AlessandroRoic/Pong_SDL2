#include "Timer.hpp"
#include <memory>
#include <utility>

SDL_TimerID Timer::setTimeout(Uint32 delay, std::function<void()> callback) {
  std::unique_ptr<std::function<void()>> callbackPtr =
      std::make_unique<std::function<void()>>(std::move(callback));

  SDL_TimerID timerID = SDL_AddTimer(
      delay,
      [](Uint32 interval, void* param) -> Uint32 {
        std::function<void()>& callback =
            *static_cast<std::function<void()>*>(param);
        callback();
        return 0;
      },
      callbackPtr.get());

  callbackPtr.release();

  return timerID;
}
