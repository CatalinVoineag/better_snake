#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "Assets.h"
#include "Engine/Window.h"
#include "Grid.h"
#include "RestartButton.h"
#include "ScoreCounter.h"
#include "GameSettings.h"
#include <memory>

class SnakeUI {
public:
  SnakeUI(Engine::Window *GameWindow)
    : ScoreCount{AssetList},
      Settings{},
      GridObj{AssetList},
      GameWindow{GameWindow},
      RestartBtn{
        Config::WINDOW_WIDTH - 150,
        Config::GRID_HEIGHT + Config::PADDING * 2,
        150 - Config::PADDING,
        Config::FOOTER_HEIGHT - Config::PADDING
      }
  {
    Settings.OrangeButtonCallback([this](SDL_Color color) {GridObj.ChangeCellsColor(color);});
    Settings.BlueButtonCallback([this](SDL_Color color) {GridObj.ChangeCellsColor(color);});
    Settings.PurpleButtonCallback([this](SDL_Color color) {GridObj.ChangeCellsColor(color);});
  }

  void HandleEvent(const SDL_Event& E) {
    if (E.type == UserEvents::GAME_START) {
      // ButtonData* data{static_cast<ButtonData*>(E.user.data1)};
      // bool test = SDL_SetWindowSize(GameWindow->GetWindow(), 1920, 1080);
      // Config::CheckSDLError("Change window size");
      // GridObj = std::make_unique<Grid>(AssetList, data->Rows, data->Columns);
      RenderMenu = false;
    } else if (E.type == UserEvents::GAME_PAUSED) {
      RenderMenu = true;
    } 

    if (RenderMenu) {
      Settings.HandleEvent(E);
    } else {  
      GridObj.HandleEvent(E);
      ScoreCount.HandleEvent(E);
      RestartBtn.HandleEvent(E);
    }
  }

  void Tick(Uint64 DeltaTime) {
    if (!RenderMenu) {
      GridObj.Tick(DeltaTime);
    }
  }

  void Render(SDL_Surface* Surface) {
    if (RenderMenu) {
      Settings.Render(Surface);
    } else {
      GridObj.Render(Surface);
      ScoreCount.Render(Surface);
      RestartBtn.Render(Surface);
    }
  }

private:
  Assets AssetList;
  Grid GridObj;
  GameSettings Settings;
  ScoreCounter ScoreCount;
  RestartButton RestartBtn;
  bool RenderMenu{true};
  Engine::Window* GameWindow{};
};
