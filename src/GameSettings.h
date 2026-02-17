#pragma once
#include<SDL3/SDL.h>
#include <SDL3/SDL_pixels.h>
#include <unordered_map>
#include "Globals.h"
#include "SettingsButton.h"

struct ButtonData {
  int Rows;
  int Columns;
};

class GameSettings {
public:
  GameSettings()
  : BackgroundRect{0, 0, Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT},
    BackgroundColor{Config::SETTINGS_BACKGROUD_COLOR},
    GridSmall{200, 200, 120, 50, "Small", &GridSmallValues},
    GridMedium{200, 400, 120, 50, "Medium", &GridMediumValues},
    GridBig{200, 600, 120, 50, "Big", &GridBigValues}
  {}

  void HandleEvent(const SDL_Event& E) {
    GridSmall.HandleEvent(E);
    GridMedium.HandleEvent(E);
    GridBig.HandleEvent(E);
  }

  void Render(SDL_Surface* Surface) {
    SDL_FillSurfaceRect(
      Surface,
      &BackgroundRect,
      SDL_MapRGB(
        SDL_GetPixelFormatDetails(Surface->format),
        nullptr,
        BackgroundColor.r,
        BackgroundColor.g,
        BackgroundColor.b
      )
    );
    GridSmall.Render(Surface);
    GridMedium.Render(Surface);
    GridBig.Render(Surface);
  }

private:
  SDL_Rect BackgroundRect;
  SDL_Color BackgroundColor;

  SettingsButton GridSmall;
  SettingsButton GridMedium;
  SettingsButton GridBig;
  ButtonData GridSmallValues{ .Rows = 10, .Columns = 15};
  ButtonData GridMediumValues{ .Rows = 20, .Columns = 30};
  ButtonData GridBigValues{ .Rows = 30, .Columns = 50};
};
