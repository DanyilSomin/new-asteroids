#include "surface.h"

#include <SDL2/SDL.h>

#include "sdlassert.h"

namespace sdlw {

Surface::Surface(SDL_Surface *surface)
  : _surface{ surface } {
  sdlAssert(surface);
}

Surface::~Surface() {
  SDL_FreeSurface(_surface.get());
}

SDL_Surface *Surface::get() const {
  return _surface.get();
}

}
