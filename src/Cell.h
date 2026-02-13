#pragma once
#include <SDL3/SDL.h>
#include "Assets.h"
#include "SnakeData.h"

enum class CellState { Snake, Apple, Empty };

class Cell {
public:
  Cell(int Row, int Column, Assets& AssetList);
  bool PlaceApple();
  void HandleEvent(const SDL_Event& E);
  void Tick(Uint64 DeltaTime);
  void Render(SDL_Surface* Surface);

private:
  void Reset();
  void Advance(const SDL_UserEvent& E);
  void GrowHead(float DeltaTime);
  void ShrinkTail(float DeltaTime);

  int Row;
  int Column;
  Assets& AssetList;
  SDL_Rect BackgroundRect;
  SDL_Color BackgroundColor;
  CellState State;
  int SnakeDuration{0};
  SDL_Color SnakeColor{Config::SNAKE_COLOR};
  SDL_Rect SnakeRect;
  float FillPercent{0.0f};
  MovementDirection FillDirection{Right};
};
