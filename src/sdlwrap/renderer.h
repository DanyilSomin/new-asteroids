#pragma once

#include "moveptr.h"

struct SDL_Renderer;

namespace sdlw {

class Window;
class Surface;
class Texture;

class Renderer {
public:
  explicit Renderer(Window &window);

  explicit Renderer(Renderer &&) = default;

  ~Renderer();

  SDL_Renderer *get() const;

  Texture createTextureFromSurface(const Surface &surface) const;

private:
  MovePtr<SDL_Renderer> _renderer;
};

}
