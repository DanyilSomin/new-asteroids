#include "renderer.h"

#include "sdlassert.h"
#include "surface.h"
#include "texture.h"
#include "window.h"

#include <SDL2/SDL.h>

namespace sdlw {

Renderer::Renderer(Window &window)
  : _renderer{ SDL_CreateRenderer(window.get(), -1,
                                  SDL_RENDERER_ACCELERATED) } {
  sdlw::sdlAssert(_renderer.get());
}

Renderer::~Renderer() {
  SDL_DestroyRenderer(_renderer.get());
}

SDL_Renderer *Renderer::get() const {
  return _renderer.get();
}

Texture Renderer::createTextureFromSurface(const Surface &surface) const {
  return Texture{ SDL_CreateTextureFromSurface(
    const_cast<SDL_Renderer *>(get()), surface.get()) };
}

}
