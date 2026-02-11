#pragma once
#include <SDL3/SDL.h>
#include "Assets.h"
#include "Grid.h"

class SnakeUI {
public:
  SnakeUI(): GridObj(AssetList) {}

  void HandleEvent(const SDL_Event& E) {
    GridObj.HandleEvent(E);
  }
  void Tick(Uint64 DeltaTime) {
    GridObj.Tick(DeltaTime);
  }
  void Render(SDL_Surface* Surface) {
    GridObj.Render(Surface);
  }

private:
  Assets AssetList;
  Grid GridObj;
};
