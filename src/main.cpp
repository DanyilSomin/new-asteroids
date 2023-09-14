#include <SDL3/SDL.h>
#include <iostream>

int main() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cout << "Failed to initialize the SDL library\n";
    std::cout << "SDL Error: " << SDL_GetError() << "\n";
    return -1;
  }

  SDL_Window *window = SDL_CreateWindow("SDL Window", 680, 480, 0);

  if (!window) {
    std::cout << "Failed to create window\n";
    std::cout << "SDL Error: " << SDL_GetError() << "\n";
    return -1;
  }

  SDL_Surface *window_surface = SDL_GetWindowSurface(window);

  if (!window_surface) {
    std::cout << "Failed to get the surface from the window\n";
    std::cout << "SDL Error: " << SDL_GetError() << "\n";
    return -1;
  }

  bool keep_window_open = true;
  while (keep_window_open) {
    SDL_Event e;
    while (SDL_PollEvent(&e) > 0) {
      switch (e.type) {
      case SDL_EVENT_QUIT:
        keep_window_open = false;
        break;
      }

      SDL_UpdateWindowSurface(window);
    }
  }
}
