#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include "GameObject.h"
#include "Config.h"

class Scene {
public:
  Scene() {
    Objects.emplace_back(
      "dwarf.png",
      Vec2{
        2 * PIXELS_PER_METER,
        4 * PIXELS_PER_METER
      },
      2.28f * PIXELS_PER_METER,
      1.7f * PIXELS_PER_METER,
      *this
    );

    Objects.emplace_back(
      "dragon.png",
      Vec2{
        30.0f * PIXELS_PER_METER,
        1.0f * PIXELS_PER_METER
      },
      2.0f * PIXELS_PER_METER,
      2.0f * PIXELS_PER_METER,
      *this
    );
  }

  SDL_Rect GetViewport() const {
    return Viewport;
  }

  const GameObject& GetPlayerCharacter() const {
    return Objects[0];
  } 

  void HandleEvent(SDL_Event& E) {
    for (GameObject& Object : Objects) {
      Object.HandleEvent(E);
    }
  }

  void Tick(float DeltaTime) {
    for (GameObject& Object : Objects) {
      Object.Tick(DeltaTime);
    }
  }

  void Render(SDL_Surface* Surface) {
    SDL_GetSurfaceClipRect(Surface, &Viewport);
    for (GameObject& Object : Objects) {
      Object.Render(Surface);
    }
  }

private:
  std::vector<GameObject> Objects;
  SDL_Rect Viewport;
};
