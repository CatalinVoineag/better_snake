#pragma once
#include <vector>
#include "Cell.h"

class Grid {
public:
  Grid(Assets& AssetList) {
    using namespace Config;
    Cells.reserve(GRID_ROWS * GRID_COLUMNS);

    for (int R{0}; R < GRID_ROWS; ++R) {
      for (int C{0}; C < GRID_COLUMNS; ++C) {
        Cells.emplace_back(R, C, AssetList);
      }
    }
  }

  void HandleEvent(const SDL_Event& E) {
    for (auto& Cell : Cells) {
      Cell.HandleEvent(E);
    }
  }

  void Tick(Uint64 DeltaTime) {
    for (auto& Cell : Cells) {
      Cell.Tick(DeltaTime);
    }
  }

  void Render(SDL_Surface* Surface) {
    for (auto& Cell : Cells) {
      Cell.Render(Surface);
    }
  }

private:
  std::vector<Cell> Cells;
};
