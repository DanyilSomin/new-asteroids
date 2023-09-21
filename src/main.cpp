#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL_image.h>

#include <string>

#include "sdlwrap/font.h"
#include "sdlwrap/renderer.h"
#include "sdlwrap/sdlassert.h"
#include "sdlwrap/sdlwrap.h"
#include "sdlwrap/surface.h"
#include "sdlwrap/texture.h"
#include "sdlwrap/window.h"

constexpr int speed                   = 1000;
static constexpr Uint64 frameInterval = 8; // ~ 120+fps

Uint64 getTimeBeforeNext(Uint64 now, Uint64 next) {
  if (now >= next) return 0;

  return next - now;
}

int main() {
  sdlw::init();

  sdlw::Window window{ "Game" };

  sdlw::Renderer renderer{ window };

  sdlw::Font font("/font.ttf", 50);

  auto surface = font.renderTextSolid("HELLO WORLD", { 255, 255, 255, 0 });

  const auto texture = renderer.createTextureFromSurface(surface);

  SDL_Texture *imageTexture = IMG_LoadTexture(renderer.get(), "/image.png");
  sdlw::sdlAssert(imageTexture);

  SDL_FRect imageRect;
  imageRect.x = 0;
  imageRect.y = 0;

  int w, h;
  sdlw::sdlAssert(SDL_QueryTexture(imageTexture, NULL, NULL, &w, &h));
  imageRect.w = w / 2;
  imageRect.h = h / 2;

  int numKeys            = 0;
  const Uint8 *keyStates = SDL_GetKeyboardState(&numKeys);
  sdlw::sdlAssert(keyStates);

  SDL_Event event;
  bool close = false;
  Uint64 timeLast{ SDL_GetTicks64() };

  while (!close) {
    const auto timeNow{ SDL_GetTicks64() };
    const auto timeElapsed = timeNow - timeLast;
    timeLast               = timeNow;

    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT:
          close = true;
          break;
        default:
          break;
      }
    }

    const auto shift{ speed * timeElapsed / 1000.0 };
    if (keyStates[SDL_SCANCODE_A]) {
      rect.x -= shift;
    }
    if (keyStates[SDL_SCANCODE_LEFT]) {
      imageRect.x -= shift;
    }
    if (keyStates[SDL_SCANCODE_D]) {
      rect.x += shift;
    }
    if (keyStates[SDL_SCANCODE_RIGHT]) {
      imageRect.x += shift;
    }
    if (keyStates[SDL_SCANCODE_W]) {
      rect.y -= shift;
    }
    if (keyStates[SDL_SCANCODE_UP]) {
      imageRect.y -= shift;
    }
    if (keyStates[SDL_SCANCODE_S]) {
      rect.y += shift;
    }
    if (keyStates[SDL_SCANCODE_DOWN]) {
      imageRect.y += shift;
    }

    SDL_RenderClear(renderer.get());
    SDL_SetRenderDrawColor(renderer.get(), 255, 255, 255, 255);
    SDL_RenderCopyF(renderer.get(), imageTexture, NULL, &imageRect);
    SDL_RenderCopyF(renderer.get(), texture, NULL, &rect);
    SDL_SetRenderDrawColor(renderer.get(), 0, 0, 0, 255);

    SDL_RenderPresent(renderer.get());

    SDL_Delay(getTimeBeforeNext(SDL_GetTicks64(), timeNow + frameInterval));
  }

  SDL_DestroyRenderer(renderer.get());

  sdlw::quit();

  return 0;
}
