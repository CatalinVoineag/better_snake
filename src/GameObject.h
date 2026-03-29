#pragma once
#include <SDL3/SDL.h>
#include "Vec2.h"
#include "Image.h"
#include "Config.h"
#include <iostream>

class Scene;

class GameObject {
 public:
  GameObject(
    const std::string& ImagePath,
    const Vec2& InitialPosition,
    const Scene& Scene ) : ImageClass{ImagePath},
                           Position{InitialPosition},
                           SceneClass{Scene} {}
  Vec2 Position;
  Vec2 Direction{1, 0};
  float MaximumSpeed{2.0f * PIXELS_PER_METER};
  Vec2 Velocity {
    4 * PIXELS_PER_METER,
    -6 * PIXELS_PER_METER
  };
  Vec2 Acceleration{0, 9.8f * PIXELS_PER_METER};

  void HandleEvent(SDL_Event& E) {
    if (E.type == SDL_EVENT_KEY_DOWN) {
      switch (E.key.key) {
        case SDLK_LEFT:
          Velocity.x = -4.0f * PIXELS_PER_METER;
          break;
        case SDLK_RIGHT:
          Velocity.x = 4.0f * PIXELS_PER_METER;
          break;
      }
    }
  }
  void Tick(float DeltaTime) {
    Vec2 PreviousPosition{Position};

    Velocity += Acceleration * DeltaTime;

    Position += Velocity * DeltaTime;
    std::cout << "\nIntended Speed = "
    << MaximumSpeed
    << ", Actual Speed = "
    << Position.GetDistance(PreviousPosition) / DeltaTime;
  }
  void Render(SDL_Surface* Surface);

 private:
  Image ImageClass;
  const Scene& SceneClass;
};
