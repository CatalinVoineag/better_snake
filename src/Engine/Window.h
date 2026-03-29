#pragma once
#include <SDL3/SDL.h>

class Window {
public:
  Window() {
    SDLWindow = SDL_CreateWindow(
      "My Program", 600, 300, 0
    );
  }

  void Render() {
    const auto* Fmt = SDL_GetPixelFormatDetails(
      GetSurface()->format
    );

    SDL_FillSurfaceRect(
      GetSurface(),
      nullptr,
      SDL_MapRGB(Fmt, nullptr, 50, 50, 50)
    );
  }

  void Update() {
    SDL_UpdateWindowSurface(SDLWindow);
  }

  SDL_Surface* GetSurface() const {
    return SDL_GetWindowSurface(SDLWindow);
  }

  SDL_Window* GetRaw() const {
      return SDLWindow;
  }

  Window(const Window&) = delete;
  Window& operator=(const Window&) = delete;

  ~Window() {
    if (SDLWindow && SDL_WasInit(SDL_INIT_VIDEO)) {
      SDL_DestroyWindow(SDLWindow);
    }
  }

private:
  SDL_Window* SDLWindow{nullptr};
};
