#pragma once 
#include <SDL3/SDL.h>
#include <SDL3/SDL_surface.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include "../Globals.h"

namespace Engine {
  class Text {
  public:
    Text(const std::string& InitialText, int FontSize)
      : Content(InitialText), Font(nullptr), TextSurface(nullptr) {
      Font = TTF_OpenFont(
        Config::FONT.c_str(), (float)FontSize
      );
      Config::CheckSDLError("Opening Font");
      SetText(InitialText);
    }

    ~Text() {
      if (TextSurface) {
        SDL_DestroySurface(TextSurface);
      }
      if (TTF_WasInit() && Font) {
        TTF_CloseFont(Font);
      }
    }

    Text(const Text&) = delete;
    Text& operator=(const Text&) = delete;

    void SetText(const std::string& NewText) {
      Content = NewText;

      if (TextSurface) {
        SDL_DestroySurface(TextSurface);
      }
      TextSurface = TTF_RenderText_Blended(
        Font, Content.c_str(), 0, Config::FONT_COLOR
      );

      Config::CheckSDLError("Creating Text Surface");
    }

    void Render(SDL_Surface* Surface, SDL_Rect* TargetRect) {
      SDL_BlitSurface(
        TextSurface, nullptr,
        Surface, TargetRect
      );
    }

  private:
    std::string Content;
    TTF_Font* Font{nullptr};
    SDL_Surface* TextSurface{nullptr};
  };
}
