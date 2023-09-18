#pragma once

#include <type_traits>

#include <SDL_stdinc.h>

namespace sdlw {

void sdlAssert(bool result);
void sdlAssert(SDL_bool result);

void sdlAssert(auto result) {
  sdlAssert(std::is_pointer_v<typeof(result)> == static_cast<bool>(result));
}

}
