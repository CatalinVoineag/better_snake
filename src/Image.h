#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <string>
#include <iostream>

class Image {
 public:
  Image() = default;
  Image(const std::string& ImagePath) {
    ImageSurface = IMG_Load(ImagePath.c_str());
    if (!ImageSurface) {
      std::cout << "Error creating image: "
        << SDL_GetError();
    }
  }

  void Render(
    SDL_Surface* Surface, const Vec2& Pos
  ) {
    if (ImageSurface) {
      SDL_Rect Rect{
        int(Pos.x), int(Pos.y),
        ImageSurface->w, ImageSurface->h
      };
      SDL_BlitSurface(
        ImageSurface, nullptr, Surface, &Rect);
    }
  }

  // Move constructor
  Image(Image&& Other) noexcept
  : ImageSurface(Other.ImageSurface) {
    Other.ImageSurface = nullptr;
  }

  ~Image() {
    if (ImageSurface) {
      SDL_DestroySurface(ImageSurface);
    }
  }

  // Prevent copying
  Image(const Image&) = delete;
  Image& operator=(const Image&) = delete;

 private:
  SDL_Surface* ImageSurface{nullptr};
};
