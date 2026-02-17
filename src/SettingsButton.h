#pragma once
#include<SDL3/SDL.h>
#include <SDL3/SDL_pixels.h>
#include <functional>
#include "Globals.h"
#include "Engine/Text.h"

class SettingsButton {
public:
  SettingsButton(int x, int y, int w, int h, std::string name, void* Data)
  : ButtonRect{x, y, w, h},
    Text{name, 20},
    Data{Data},
    CurrentColor(Config::BUTTON_COLOR) {}

  using DelegateType = std::function<void(SDL_Color& color)>;
  void setSnakeColor(DelegateType D) {
    onClick = D;
  }

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
      if (onClick) onClick(*static_cast<SDL_Color*>(Data));
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
  DelegateType onClick;
};
