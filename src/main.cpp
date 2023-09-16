#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <string>

constexpr int speed = 1000;
static constexpr Uint64 frameInterval = 8; // ~ 120+fps

void logError() {
  SDL_Log("SDL error: %s!", SDL_GetError());
  exit(-1);
}

Uint64 getTimeBeforeNext(Uint64 now, Uint64 next) {
  if (now >= next)
    return 0;

  return next - now;
}

void get_text_and_rect(SDL_Renderer *renderer, int x, int y, char *text,
                       TTF_Font *font, SDL_Texture **texture, SDL_FRect *rect) {
  int text_width;
  int text_height;
  SDL_Surface *surface;
  SDL_Color textColor = {255, 255, 255, 0};

  surface = TTF_RenderText_Solid(font, text, textColor);
  if (!surface)
    logError();

  *texture = SDL_CreateTextureFromSurface(renderer, surface);
  if (!*texture)
    logError();

  text_width = surface->w;
  text_height = surface->h;
  SDL_FreeSurface(surface);
  rect->x = x;
  rect->y = y;
  rect->w = text_width;
  rect->h = text_height;
}

int main() {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    logError();
  }

  SDL_Window *window =
      SDL_CreateWindow("GAME", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       1280, 720, SDL_WINDOW_RESIZABLE);
  if (!window)
    logError();

  SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");

  SDL_Renderer *renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer)
    logError();

  SDL_RendererInfo info;
  SDL_GetRendererInfo(renderer, &info);

  TTF_Init();
  TTF_Font *font = TTF_OpenFont("/font.ttf", 50);
  if (!font)
    logError();

  SDL_FRect rect;
  SDL_Texture *texture;

  std::string helloWorld{"HELLO WORLD"};
  get_text_and_rect(renderer, 0, 0, helloWorld.data(), font, &texture, &rect);

  int numKeys = 0;
  const Uint8 *keyStates = SDL_GetKeyboardState(&numKeys);
  if (!keyStates)
    logError();

  SDL_Event event;
  bool close = false;
  Uint64 timeLast{SDL_GetTicks64()};

  while (!close) {
    const auto timeNow{SDL_GetTicks64()};
    const auto timeElapsed = timeNow - timeLast;
    timeLast = timeNow;

    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_QUIT:
        close = true;
        break;
      default:
        break;
      }
    }

    const auto shift{speed * timeElapsed / 1000.0};
    if (keyStates[SDL_SCANCODE_A] || keyStates[SDL_SCANCODE_LEFT]) {
      rect.x -= shift;
    }
    if (keyStates[SDL_SCANCODE_D] || keyStates[SDL_SCANCODE_RIGHT]) {
      rect.x += shift;
    }
    if (keyStates[SDL_SCANCODE_W] || keyStates[SDL_SCANCODE_UP]) {
      rect.y -= shift;
    }
    if (keyStates[SDL_SCANCODE_S] || keyStates[SDL_SCANCODE_DOWN]) {
      rect.y += shift;
    }

    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderCopyF(renderer, texture, NULL, &rect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    SDL_RenderPresent(renderer);

    const auto delay =
        getTimeBeforeNext(SDL_GetTicks64(), timeNow + frameInterval);
    SDL_Delay(delay);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  return 0;
}
