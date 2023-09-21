#include "texture.h"

#include <SDL2/SDL.h>

#include "sdlassert.h"

namespace sdlw {

Texture::Texture(SDL_Texture *texture)
  : _texture{ texture } {
  sdlAssert(texture);
}

Texture::~Texture() {
  SDL_DestroyTexture(_texture.get());
}

SDL_Texture *Texture::get() const {
  return _texture.get();
}

}
