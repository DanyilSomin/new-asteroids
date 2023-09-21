#pragma once

#include <string>

#include "moveptr.h"

typedef struct _TTF_Font TTF_Font;
struct SDL_Surface;
struct SDL_Color;

namespace sdlw {

class Surface;

class Font {
public:
  explicit Font(const std::string &name, size_t size);

  explicit Font(Font &&) = default;

  ~Font();

  TTF_Font *get() const;

  Surface renderTextSolid(const std::string &text,
                          const SDL_Color &color) const;

private:
  MovePtr<TTF_Font> _font;
};

}
