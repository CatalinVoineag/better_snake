#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_surface.h>

class Rectangle {
public: 
  void Render(SDL_Surface* Surface, float Scale) {
    SDL_Rect Rect{
      0, 0,
      int (350 * Scale), int (200 * Scale)
    };

    SDL_FillSurfaceRect(
      Surface, &Rect,
      SDL_MapRGB(
        SDL_GetPixelFormatDetails(Surface->format),
        nullptr, 150, 50, 50
      )
    );
  }
};
