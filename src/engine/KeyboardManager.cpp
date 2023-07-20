#include "KeyboardManager.hpp"
#include <SDL_events.h>

void KeyboardManager::handleEvent(SDL_Event event) {
  const auto code = event.key.keysym.scancode;
  if (event.type == SDL_KEYDOWN) {
    pressedKeys.insert(code);
  } else if (event.type == SDL_KEYUP) {
    pressedKeys.erase(code);
  }
}
