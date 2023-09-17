#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <string>

#include "sdl-wrap/sdl-wrap.h"

constexpr int speed                   = 1000;
static constexpr Uint64 frameInterval = 8; // ~ 120+fps

Uint64 getTimeBeforeNext(Uint64 now, Uint64 next) {
  if (now >= next) return 0;

  return next - now;
}

void get_text_and_rect(SDL_Renderer *renderer, int x, int y, char *text,
                       TTF_Font *font, SDL_Texture **texture, SDL_FRect *rect) {
  int text_width;
  int text_height;
  SDL_Surface *surface;
  SDL_Color textColor = { 255, 255, 255, 0 };

  surface = TTF_RenderText_Solid(font, text, textColor);
  sdlw::sdlAssert(surface);

  *texture = SDL_CreateTextureFromSurface(renderer, surface);
  sdlw::sdlAssert(texture);

  text_width  = surface->w;
  text_height = surface->h;
  SDL_FreeSurface(surface);
  rect->x = x;
  rect->y = y;
  rect->w = text_width;
  rect->h = text_height;
}

int main() {
  sdlw::init();

  SDL_Window *window =
    SDL_CreateWindow("GAME", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                     1280, 720, SDL_WINDOW_RESIZABLE);
  sdlw::sdlAssert(window);

  SDL_Renderer *renderer =
    SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  sdlw::sdlAssert(renderer);

  SDL_RendererInfo info;
  SDL_GetRendererInfo(renderer, &info);

  TTF_Init();
  TTF_Font *font = TTF_OpenFont("/font.ttf", 50);
  sdlw::sdlAssert(font);

  SDL_FRect rect;
  SDL_Texture *texture;

  std::string helloWorld{ "HELLO WORLD" };
  get_text_and_rect(renderer, 0, 0, helloWorld.data(), font, &texture, &rect);

  SDL_Texture *imageTexture = IMG_LoadTexture(renderer, "/image.png");
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

    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderCopyF(renderer, imageTexture, NULL, &imageRect);
    SDL_RenderCopyF(renderer, texture, NULL, &rect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    SDL_RenderPresent(renderer);

    SDL_Delay(getTimeBeforeNext(SDL_GetTicks64(), timeNow + frameInterval));
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  sdlw::quit();

  return 0;
}
