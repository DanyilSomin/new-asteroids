#include "sdlwrap.h"

#include <SDL2/SDL.h>
#include <SDL_ttf.h>

#include "sdlassert.h"

namespace sdlw {

void init() {
  sdlAssert(SDL_Init(SDL_INIT_EVERYTHING));
  sdlAssert(TTF_Init());

  const auto res = SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");

  sdlAssert(res);
}

void quit() {
  SDL_Quit();
  TTF_Quit();
}

}
