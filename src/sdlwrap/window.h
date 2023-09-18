#pragma once

#include <string>

#include "moveptr.h"

struct SDL_Window;

namespace sdlw {

class Window {
public:
  explicit Window(const std::string &name);

  explicit Window(Window &&)   = default;
  Window &operator=(Window &&) = default;

  ~Window();

  const SDL_Window *get() const;
  SDL_Window *get();

private:
  MovePtr<SDL_Window> _window;
};

}
