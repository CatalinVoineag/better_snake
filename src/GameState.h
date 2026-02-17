#pragma once
#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include "Globals.h"
#include "SnakeData.h"

class GameState {
public:
  void HandleEvent(const SDL_Event& E) {
    if (E.type == SDL_EVENT_KEY_DOWN) {
      HandleKeyEvent(E.key);
    } else if (E.type == UserEvents::APPLE_EATEN) {
      ++Snake.Length;
      if (Snake.Length == Config::MAX_LENGTH) {
        SDL_Event Event{};
        Event.type = UserEvents::GAME_WON;
        SDL_PushEvent(&Event);
      }
    } else if (E.type == UserEvents::RESTART_GAME) {
      RestartGame();
    } else if (E.type == UserEvents::GAME_LOST || E.type == UserEvents::GAME_WON) {
      IsGameOver = true;
    }
  }

  void Tick(Uint64 DeltaTime) {
    if (IsPaused || IsGameOver) return;
    ElapsedTime += DeltaTime;

    if (ElapsedTime >= Config::ADVANCE_INTERVAL) {
      ElapsedTime = 0;
      UpdateSnake();
    }
  }

private:
  void HandleKeyEvent(const SDL_KeyboardEvent& E) {
    if (IsGameOver) return;

    switch (E.key) {
      case SDLK_UP:
      case SDLK_W:
        if (Snake.Direction != Down) {
          NextDirection = Up;
        }
        break;
      case SDLK_DOWN:
      case SDLK_S:
        if (Snake.Direction != Up) {
          NextDirection = Down;
        }
        break;
      case SDLK_LEFT:
      case SDLK_A:
        if (Snake.Direction != Right) {
          NextDirection = Left;
        }
        break;
      case SDLK_RIGHT:
      case SDLK_D:
        if (IsPaused) {
          IsPaused = false;
          NextDirection = Right;
          UpdateSnake();
        }
        if (Snake.Direction != Left) {
          NextDirection = Right;
        }
        break;
      case SDLK_ESCAPE:
        IsPaused = true;
        SDL_Event Event{};
        Event.type = UserEvents::GAME_PAUSED;
        SDL_PushEvent(&Event);
        break;
    }
  }

  void StartGame() {
  }

  void UpdateSnake() {
    Snake.Direction = NextDirection;
    switch (NextDirection) {
      case Up:
        Snake.HeadRow--;
        break;
      case Down:
        Snake.HeadRow++;
        break;
      case Left:
        Snake.HeadCol--;
        break;
      case Right:
        Snake.HeadCol++;
        break;
    }
    if (
        Snake.HeadRow < 0 ||
        Snake.HeadRow >= Config::GRID_ROWS ||
        Snake.HeadCol < 0 ||
        Snake.HeadCol >= Config::GRID_COLUMNS
    ) {
      SDL_Event Event{};
      Event.type = UserEvents::GAME_LOST;
      SDL_PushEvent(&Event);
    } else {
      SDL_Event Event{};
      Event.type = UserEvents::ADVANCE;
      Event.user.data1 = &Snake;
      SDL_PushEvent(&Event);
    }
  }

    void RestartGame() {
      IsPaused = true;
      IsGameOver = false;
      ElapsedTime = 0;
      Snake = {
        .HeadRow = Config::GRID_ROWS / 2,
        .HeadCol = 3,
        .Length = 2,
        .Direction = Right
      };

      NextDirection = Right;
    }


  // Direction the snake will move in when the
  // game state next advances
  MovementDirection NextDirection{Right};
  Uint64 ElapsedTime{0};
  SnakeData Snake{
    .HeadRow = Config::GRID_ROWS / 2,
    .HeadCol = 3,
    .Length = 2,
    .Direction = Right
  };
  bool IsPaused{true};
  bool IsGameOver{false};
};
