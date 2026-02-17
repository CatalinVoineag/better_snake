#pragma once
#include <vector>
#include "Cell.h"
#include "Engine/Random.h"

class Grid {
public:
  Grid(Assets& AssetList, int Rows, int Columns)
    : Rows{Rows}, Columns{Columns} 
  {
    using namespace Config;
    Cells.reserve(Rows * Columns);

    std::cout << "Creating grid\n";
    for (int R{0}; R < Rows; ++R) {
      for (int C{0}; C < Columns; ++C) {
        Cells.emplace_back(R, C, AssetList);
      }
    }
  }

  void HandleEvent(const SDL_Event& E) {
    for (auto& Cell : Cells) {
      Cell.HandleEvent(E);
    }

    if (E.type == UserEvents::APPLE_EATEN) {
      PlaceRandomApple();
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
  void PlaceRandomApple() {
    while (true) {
      int RandomIndex{Engine::Random::Int(0, int(Cells.size()) - 1)};
      if (Cells[RandomIndex].PlaceApple()) {
        break;
      }
    }
  }

  std::vector<Cell> Cells;
  int Rows;
  int Columns;
};
