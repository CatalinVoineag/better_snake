#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <string>
#include "../Globals.h"

namespace Engine {
  class Image {
  public:
    Image(const std::string& Path) {
      ImageSurface = IMG_Load(Path.c_str());
      Config::CheckSDLError("Loading Image");
    }

    ~Image() {
      if (ImageSurface) {
        SDL_DestroySurface(ImageSurface);
      }
    }

    void Render(SDL_Surface* Surface, SDL_Rect* Rect) {
      SDL_BlitSurfaceScaled(
        ImageSurface, nullptr,
        Surface, Rect,
        SDL_SCALEMODE_LINEAR
      );
    }

    Image(const Image&) = delete;
    Image& operator=(const Image&) = delete;

  private:
    SDL_Surface* ImageSurface{nullptr};
  };
}
