#pragma once

#include <string>

#include "moveptr.h"

struct SDL_Window;

namespace sdlw {

class Window {
public:
  explicit Window(const std::string &name);

  explicit Window(Window &&) = default;

  ~Window();

  SDL_Window *get() const;

private:
  MovePtr<SDL_Window> _window;
};

}
