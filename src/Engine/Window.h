#pragma once
#include <SDL3/SDL.h>
#include "../Globals.h"

namespace Engine {
  class Window {
  public:
    Window() {
      SDLWindow = SDL_CreateWindow(
        Config::GAME_NAME.c_str(),
        Config::WINDOW_WIDTH,
        Config::WINDOW_HEIGHT,
        0
      );
      Config::CheckSDLError("Creating Window");
    };

    ~Window() {
      if (SDLWindow && SDL_WasInit(SDL_INIT_VIDEO)) {
        SDL_DestroyWindow(SDLWindow);
      }
    }

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    void Render() {
      const auto* Fmt = SDL_GetPixelFormatDetails(
        GetSurface()-> format
      );
      SDL_FillSurfaceRect(
        GetSurface(), nullptr,
        SDL_MapRGB(
          Fmt, nullptr,
          Config::BACKGROUND_COLOR.r,
          Config::BACKGROUND_COLOR.g,
          Config::BACKGROUND_COLOR.b
        )
      );
    }

    void Update() {
      SDL_UpdateWindowSurface(SDLWindow);
    }

    SDL_Surface* GetSurface() {
      return SDL_GetWindowSurface(SDLWindow);
    }

  private:
    SDL_Window* SDLWindow{nullptr};
  };
}
