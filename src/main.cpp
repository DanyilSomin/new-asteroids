#include <string>

#include "sdlw/font.h"
#include "sdlw/keystates.h"
#include "sdlw/renderer.h"
#include "sdlw/sdlw.h"
#include "sdlw/surface.h"
#include "sdlw/texture.h"
#include "sdlw/window.h"

constexpr int speed                     = 1000;
static constexpr uint64_t frameInterval = 8; // ~ 120+fps

uint64_t getTimeBeforeNext(uint64_t now, uint64_t next) {
  if (now >= next) return 0;

  return next - now;
}

int main() {
  sdlw::init();

  const sdlw::Window window{ "Game" };
  const sdlw::Renderer renderer{ window };
  const sdlw::Font font{ "/font.ttf", 50 };

  const std::string text{ "HELLO WORLD" };
  const SDL_Color color{ 255, 255, 255, 0 };
  const auto textSurface{ font.renderTextSolid(text, color) };
  const auto textTexture{ renderer.createTextureFromSurface(textSurface) };
  SDL_FRect textRect{ 0, 0, static_cast<float>(textTexture.w()),
                      static_cast<float>(textTexture.h()) };

  const auto imageTexture{ renderer.loadImage("/image.png") };
  SDL_FRect imageRect{ 0, 0, static_cast<float>(imageTexture.w()),
                       static_cast<float>(imageTexture.h()) };

  const sdlw::KeyStates keyStates;

  SDL_Event event;
  bool close = false;
  uint64_t timeLast{ SDL_GetTicks64() };

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
    if (keyStates.check(SDL_SCANCODE_A)) {
      textRect.x -= shift;
    }
    if (keyStates.check(SDL_SCANCODE_LEFT)) {
      imageRect.x -= shift;
    }
    if (keyStates.check(SDL_SCANCODE_D)) {
      textRect.x += shift;
    }
    if (keyStates.check(SDL_SCANCODE_RIGHT)) {
      imageRect.x += shift;
    }
    if (keyStates.check(SDL_SCANCODE_W)) {
      textRect.y -= shift;
    }
    if (keyStates.check(SDL_SCANCODE_UP)) {
      imageRect.y -= shift;
    }
    if (keyStates.check(SDL_SCANCODE_S)) {
      textRect.y += shift;
    }
    if (keyStates.check(SDL_SCANCODE_DOWN)) {
      imageRect.y += shift;
    }

    renderer.clear();
    renderer.setDrawColor(255, 255, 255);
    renderer.renderCopy(imageTexture, imageRect);
    renderer.renderCopy(textTexture, textRect);
    renderer.setDrawColor(0, 0, 0);

    renderer.present();

    SDL_Delay(getTimeBeforeNext(SDL_GetTicks64(), timeNow + frameInterval));
  }

  sdlw::quit();

  return 0;
}
