#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "Window.h"
#include "Scene.h"

int main(int argc, char** argv) {
  SDL_Init(SDL_INIT_VIDEO);
  Window GameWindow;
  Scene GameScene;

  Uint64 LastTick{SDL_GetPerformanceCounter()};
  SDL_Event Event;
  bool IsRunning = true;

  while (IsRunning) {
    while (SDL_PollEvent(&Event)) {
      if (Event.type == SDL_EVENT_QUIT) {
        IsRunning = false;
      }
      GameScene.HandleEvent(Event);
    }

    Uint64 CurrentTick{SDL_GetPerformanceCounter()};
    float DeltaTime{static_cast<float>(
      CurrentTick - LastTick) /
      static_cast<float>(SDL_GetPerformanceFrequency())
    };
    LastTick = CurrentTick;

    // Tick
    GameScene.Tick(DeltaTime);

    // Render
    GameWindow.Render();
    GameScene.Render(GameWindow.GetSurface());

    // Swap
    GameWindow.Update();
  }

  SDL_Quit();
  return 0;
}
