#pragma once

#include "moveptr.h"

struct SDL_Surface;

namespace sdlw {

class Surface {
public:
  explicit Surface(SDL_Surface *surface);

  explicit Surface(Surface &&) = default;

  ~Surface();

  SDL_Surface *get() const;

private:
  MovePtr<SDL_Surface> _surface;
};

}
