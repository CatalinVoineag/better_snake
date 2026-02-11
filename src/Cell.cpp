#include "Cell.h"

Cell::Cell(int Row, int Column, Assets& AssetList)
  : Row(Row), Column(Column), AssetList{AssetList} {
}

void Cell::HandleEvent(const SDL_Event& E) {}
void Cell::Tick(Uint64 DeltaTime) {}
void Cell::Render(SDL_Surface* Surface) {}
