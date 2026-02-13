#include "Cell.h"
#include "Globals.h"
#include "SnakeData.h"
#include <SDL3/SDL_pixels.h>

Cell::Cell(int Row, int Column, Assets& AssetList)
  : Row(Row),
  Column(Column),
  AssetList{AssetList},
  BackgroundRect{
    Column * Config::CELL_SIZE + Config::PADDING,
    Row * Config::CELL_SIZE + Config::PADDING,
    Config::CELL_SIZE,
    Config::CELL_SIZE
  },
  BackgroundColor{
    (Row + Column) % 2 == 0 ? Config::CELL_COLOR_A : Config::CELL_COLOR_B
  }
{
  Reset();
}

bool Cell::PlaceApple() {
  if (State != CellState::Empty) return false;

  State = CellState::Apple;
  return true;
}

void Cell::HandleEvent(const SDL_Event& E) {
  if (E.type == UserEvents::ADVANCE) {
    Advance(E.user);
  } else if (E.type == UserEvents::APPLE_EATEN) {
    ++SnakeDuration;
  } else if (E.type == UserEvents::GAME_LOST) {
    SnakeColor = Config::SNAKE_LOST_COLOR;
  } else if (E.type == UserEvents::GAME_WON) {
    SnakeColor = Config::SNAKE_WON_COLOR;
  } else if (E.type == UserEvents::RESTART_GAME) {
    Reset();
  }
}

void Cell::Tick(Uint64 DeltaTime) {
  if (State == CellState::Snake && FillPercent < 1.0f) {
    GrowHead(float(DeltaTime));
  } else if (State != CellState::Snake && FillPercent > 0.0f) {
    ShrinkTail(float(DeltaTime));
  }
}

void Cell::GrowHead(float DeltaTime) {
  using namespace Config;
  FillPercent += DeltaTime / ADVANCE_INTERVAL;
  if (FillPercent > 1.0f) FillPercent = 1.0f;

  SnakeRect = BackgroundRect;
  if (FillDirection == Right) {
    SnakeRect.w = int(CELL_SIZE * FillPercent);
  } else if (FillDirection == Down) {
    SnakeRect.h = int(CELL_SIZE * FillPercent);
  } else if (FillDirection == Left) {
    SnakeRect.x = int(BackgroundRect.x + CELL_SIZE * (1.0f - FillPercent));
  } else if (FillDirection == Up) {
    SnakeRect.y = int(BackgroundRect.y + CELL_SIZE * (1.0f - FillPercent));
  }
}

void Cell::ShrinkTail(float DeltaTime) {
  using namespace Config;
  FillPercent -= DeltaTime / ADVANCE_INTERVAL;
  if (FillPercent < 0.0f) FillPercent = 0.0f;

  SnakeRect = BackgroundRect;
  if (FillDirection == Right) {
    SnakeRect.x = BackgroundRect.x + int(CELL_SIZE * (1.0f - FillPercent));
  } else if (FillDirection == Left) {
    SnakeRect.w = int(CELL_SIZE * FillPercent);
  } else if (FillDirection == Up) {
    SnakeRect.h = int(CELL_SIZE * FillPercent);
  } else if (FillDirection == Down) {
    SnakeRect.y = BackgroundRect.y + int(CELL_SIZE * (1.0f - FillPercent));
  }
}

void Cell::Render(SDL_Surface* Surface) {
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

  if (State == CellState::Apple) {
    AssetList.Apple.Render(Surface, &BackgroundRect);
  } else if (FillPercent > 0) {
    SDL_FillSurfaceRect(
      Surface,
      &SnakeRect,
      SDL_MapRGB(
        SDL_GetPixelFormatDetails(Surface->format),
        nullptr,
        SnakeColor.r,
        SnakeColor.g,
        SnakeColor.b
      )
    );
  }
}

void Cell::Reset() {
  SnakeRect = BackgroundRect;
  State = CellState::Empty;
  SnakeColor = Config::SNAKE_COLOR;
  SnakeDuration = 0;
  FillPercent = 0.0f;
  FillDirection = Right;

  int MiddleRow{Config::GRID_ROWS / 2};
  if (Row == MiddleRow && Column == 2) {
    State = CellState::Snake;
    SnakeDuration = 1;
    FillPercent = 1.0f;
  } else if (Row == MiddleRow && Column == 3) {
    State = CellState::Snake;
    SnakeDuration = 2;
    FillPercent = 1.0f;
  } else if (Row == MiddleRow && Column == 11) {
    State = CellState::Apple;
  }
}

void Cell::Advance(const SDL_UserEvent& E) {
  SnakeData* Data{static_cast<SnakeData*>(E.data1)};

  bool isThisCell {Data->HeadRow == Row && Data->HeadCol == Column};

  if (isThisCell) {
    if (State == CellState::Snake) {
      SDL_Event Event{};
      Event.type = UserEvents::GAME_LOST;
      SDL_PushEvent(&Event);
      return;
    }

    if (State == CellState::Apple) {
      SDL_Event Event{ .type = UserEvents::APPLE_EATEN };
      SDL_PushEvent(&Event);
    }

    State = CellState::Snake;
    SnakeDuration = Data->Length;
    FillDirection = Data->Direction;
    FillPercent = 0.0f;
  } else if (State == CellState::Snake) {
    if (SnakeDuration == Data->Length) {
      FillDirection = Data->Direction;
    }
    --SnakeDuration;
    if (SnakeDuration == 0) {
      State = CellState::Empty;
    }
  }
}
