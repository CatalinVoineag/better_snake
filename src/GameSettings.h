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
    GridBig{200, 600, 120, 50, "Big", &GridBigValues},
    SnakeOrangeColor{500, 200, 120, 50, "Orange", &Orange},
    SnakeBlueColor{500, 400, 120, 50, "Blue", &Blue},
    SnakePurpleColor{500, 600, 120, 50, "Purple", &Purple}
  {}

  void OrangeButtonCallback(std::function<void(SDL_Color)> function) {
    SnakeOrangeColor.setSnakeColor(function);
  }

  void BlueButtonCallback(std::function<void(SDL_Color)> function) {
    SnakeBlueColor.setSnakeColor(function);
  }

  void PurpleButtonCallback(std::function<void(SDL_Color)> function) {
    SnakePurpleColor.setSnakeColor(function);
  }

  void HandleEvent(const SDL_Event& E) {
    GridSmall.HandleEvent(E);
    GridMedium.HandleEvent(E);
    GridBig.HandleEvent(E);
    SnakeOrangeColor.HandleEvent(E);
    SnakeBlueColor.HandleEvent(E);
    SnakePurpleColor.HandleEvent(E);
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
    SnakeOrangeColor.Render(Surface);
    SnakeBlueColor.Render(Surface);
    SnakePurpleColor.Render(Surface);
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

  SettingsButton SnakeOrangeColor;
  SettingsButton SnakeBlueColor;
  SettingsButton SnakePurpleColor;
  SDL_Color Orange{255, 91, 0, 255};
  SDL_Color Blue {67, 117, 234, 255};
  SDL_Color Purple{191, 0, 255, 255};
};
