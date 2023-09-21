#include "font.h"

#include <SDL_ttf.h>

#include "sdlassert.h"
#include "surface.h"

namespace sdlw {

Font::Font(const std::string &name, size_t size)
  : _font{ TTF_OpenFont(name.c_str(), size) } {
  sdlAssert(_font.get());
}

Font::~Font() {
  TTF_CloseFont(get());
}

TTF_Font *Font::get() const {
  return _font.get();
}

Surface Font::renderTextSolid(const std::string &text,
                              const SDL_Color &color) const {
  return Surface{ TTF_RenderText_Solid(const_cast<TTF_Font *>(_font.get()),
                                       text.c_str(), color) };
}

}
