#ifndef PINGPONG_SDL2_KEYBOARDMANAGER_HPP
#define PINGPONG_SDL2_KEYBOARDMANAGER_HPP
#include <SDL_events.h>
#include <unordered_set>
#include <vector>

class KeyboardManager {
 public:
  std::unordered_set<SDL_Scancode> pressedKeys;
  void handleEvent(SDL_Event event);
};
#endif  //PINGPONG_SDL2_KEYBOARDMANAGER_HPP
