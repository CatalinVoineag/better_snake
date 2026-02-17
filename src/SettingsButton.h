#pragma once
#include<SDL3/SDL.h>
#include <SDL3/SDL_pixels.h>
#include <unordered_map>
#include "Globals.h"
#include "Engine/Text.h"

class SettingsButton {
public:
  SettingsButton(int x, int y, int w, int h, std::string name, void* Data)
  : ButtonRect{x, y, w, h},
    Text{name, 20},
    Data{Data},
    CurrentColor(Config::BUTTON_COLOR) {}

  void Render(SDL_Surface* Surface) {
    SDL_FillSurfaceRect(Surface, &ButtonRect,
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
    if (E.type == SDL_EVENT_MOUSE_BUTTON_DOWN && isClicked(E.button)) {
      SDL_Event Event{};
      Event.type = UserEvents::GAME_START;
      Event.user.data1 = Data;
      SDL_PushEvent(&Event);
    }
  }

private:
  bool isClicked(const SDL_MouseButtonEvent& E) {
    if (E.x >= ButtonRect.x &&
        E.x <= ButtonRect.x + ButtonRect.w &&
        E.y >= ButtonRect.y &&
        E.y <= ButtonRect.y + ButtonRect.h
      ) {
      return true;
    } 

    return false;
  }
  SDL_Rect ButtonRect;
  Engine::Text Text;
  SDL_Color CurrentColor;
  std::unordered_map<std::string, int> settingsMap;
  void* Data{nullptr};
};
