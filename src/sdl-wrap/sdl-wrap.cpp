#include "sdl-wrap.h"

#include <SDL2/sdl.h>

namespace sdlw {

void init() {
  sdlAssert(SDL_Init(SDL_INIT_EVERYTHING));

  const auto res = SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");

  sdlAssert(res);
}

void quit() {
  SDL_Quit();
}

void sdlAssert(bool ok) {
  if (!ok) {
    SDL_Log("SDL error: %s!", SDL_GetError());
    SDL_Quit();

    exit(-1);
  }
}

void sdlAssert(SDL_bool result) {
  sdlAssert(static_cast<bool>(result));
}

}
