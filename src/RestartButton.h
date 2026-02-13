#pragma once
#include <SDL3/SDL.h>
#include "Globals.h"
#include "Engine/Text.h"

class RestartButton {
public:
  RestartButton(int x, int y, int w, int h)
    : ButtonRect{x, y, w, h},
      Text{"RESTART", 20},
      CurrentColor(Config::BUTTON_COLOR) {}

  void Render(SDL_Surface* Surface) {
    SDL_FillSurfaceRect(
      Surface, &ButtonRect,
      SDL_MapRGB(
        SDL_GetPixelFormatDetails(Surface->format),
        nullptr,
        CurrentColor.r,
        CurrentColor.g,
        CurrentColor.b
      )
    );
    Text.Render(Surface, &ButtonRect);
  }

  void HandleEvent(const SDL_Event& E) {
    if (E.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
      HandleClick(E.button);
    } else if (E.type == UserEvents::GAME_LOST || E.type == UserEvents::GAME_WON) {
      CurrentColor = Config::BUTTON_HIGHLIGHT_COLOR;
    } else if (E.type == UserEvents::RESTART_GAME) {
      CurrentColor = Config::BUTTON_COLOR;
    }
  }

private:
  void HandleClick(const SDL_MouseButtonEvent& E) {
    if (
        E.x >= ButtonRect.x &&
        E.x <= ButtonRect.x + ButtonRect.w &&
        E.y >= ButtonRect.y &&
        E.y <= ButtonRect.y + ButtonRect.h
       ) {
      SDL_Event RestartEvent{ .type = UserEvents::RESTART_GAME };
      SDL_PushEvent(&RestartEvent);
    }
  }

  SDL_Rect ButtonRect;
  Engine::Text Text;
  SDL_Color CurrentColor;
};
