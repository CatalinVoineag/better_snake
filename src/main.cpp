#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "Globals.h"
#include "Engine/Window.h"
#include "SnakeUI.h"
#include "GameState.h"

int main(int, char**) {
  SDL_Init(SDL_INIT_VIDEO);
  Config::CheckSDLError("Initializing SDL");

  TTF_Init();
  Config::CheckSDLError("Initializing SDL_ttf");

  Engine::Window GameWindow{};
  SnakeUI UI{&GameWindow};
  GameState State{};

  Uint64 PreviousTick{SDL_GetTicks()};
  Uint64 CurrentTick;
  Uint64 DeltaTime;

  SDL_Event Event;
  bool IsRunning = true;
  while (IsRunning) {
    CurrentTick = SDL_GetTicks();
    DeltaTime = CurrentTick - PreviousTick;

    while (SDL_PollEvent(&Event)) {
      UI.HandleEvent(Event);
      State.HandleEvent(Event);
      if (Event.type == SDL_EVENT_QUIT) {
        IsRunning = false;
      }
    }

    UI.Tick(DeltaTime);
    State.Tick(DeltaTime);

    GameWindow.Render();
    UI.Render(GameWindow.GetSurface());

    GameWindow.Update();
    PreviousTick = CurrentTick;
  }

  TTF_Quit();
  SDL_Quit();
  return 0;
}
