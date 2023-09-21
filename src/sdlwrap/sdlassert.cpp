#include "sdlassert.h"

#include <SDL2/SDL.h>

#include "sdlwrap.h"

namespace sdlw {

void sdlAssert(bool ok) {
  if (!ok) {
    SDL_Log("SDL error: %s!", SDL_GetError());
    quit();

    exit(-1);
  }
}

void sdlAssert(SDL_bool result) {
  sdlAssert(static_cast<bool>(result));
}

}
