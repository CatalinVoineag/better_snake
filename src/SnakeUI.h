#pragma once
#include <SDL3/SDL.h>
#include "Assets.h"
#include "Grid.h"
#include "RestartButton.h"
#include "ScoreCounter.h"

class SnakeUI {
public:
  SnakeUI()
    : GridObj(AssetList),
      ScoreCount{AssetList},
      RestartBtn{
        Config::WINDOW_WIDTH - 150,
        Config::GRID_HEIGHT + Config::PADDING * 2,
        150 - Config::PADDING,
        Config::FOOTER_HEIGHT - Config::PADDING
      }
  {}

  void HandleEvent(const SDL_Event& E) {
    GridObj.HandleEvent(E);
    ScoreCount.HandleEvent(E);
    RestartBtn.HandleEvent(E);
  }
  void Tick(Uint64 DeltaTime) {
    GridObj.Tick(DeltaTime);
  }
  void Render(SDL_Surface* Surface) {
    GridObj.Render(Surface);
    ScoreCount.Render(Surface);
    RestartBtn.Render(Surface);
  }

private:
  Assets AssetList;
  Grid GridObj;
  ScoreCounter ScoreCount;
  RestartButton RestartBtn;
};
