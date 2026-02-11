#pragma once
#include <SDL3/SDL.h>
#include "Assets.h"

class Cell {
public:
  Cell(int Row, int Column, Assets& AssetList);

  void HandleEvent(const SDL_Event& E);
  void Tick(Uint64 DeltaTime);
  void Render(SDL_Surface* Surface);

private:
  int Row;
  int Column;
  Assets& AssetList;
};
