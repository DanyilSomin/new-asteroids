#include "window.h"

#include <SDL2/SDL.h>

#include "sdlassert.h"

namespace sdlw {

Window::Window(const std::string &title)
  : _window{ SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, 1280, 720,
                              SDL_WINDOW_RESIZABLE) } {
  sdlw::sdlAssert(_window.get());
}

Window::~Window() {
  SDL_DestroyWindow(_window.get());
}

SDL_Window *Window::get() const {
  return _window.get();
}

}
