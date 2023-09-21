#pragma once

#include "moveptr.h"

struct SDL_Texture;

namespace sdlw {

class Texture {
public:
  explicit Texture(SDL_Texture *texture);

  explicit Texture(Texture &&) = default;

  ~Texture();

  SDL_Texture *get() const;

private:
  MovePtr<SDL_Texture> _texture;
};

}
