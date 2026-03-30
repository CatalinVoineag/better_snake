#pragma once
#include <SDL3/SDL.h>
#include <algorithm>
#include "Vec2.h"
#include "Image.h"
#include "Config.h"
#include "BoundingBox.h"
#include <iostream>

class Scene;

class GameObject {
 public:
  GameObject(
    const std::string& ImagePath,
    const Vec2& InitialPosition,
    float Width,
    float Height,
    const Scene& SceneClass ) : ImageClass{ImagePath},
                           Position{InitialPosition},
                           SceneClass{SceneClass},
                           Bounds{SDL_FRect{
                             InitialPosition.x, InitialPosition.y,
                             Width, Height
                           }}
                           {}

  void HandleEvent(SDL_Event& E) {
    if (E.type == SDL_EVENT_KEY_DOWN) {
      if (E.key.key == SDLK_SPACE) {
        ApplyImpulse({0.0f, -15000.0f});
      }
    } else if (E.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
      if (E.button.button == SDL_BUTTON_LEFT) {
        ApplyPositionalImpulse(
          Vec2{E.button.x, E.button.y},
          10000.0f
        );
      }
    }
  }

  void Tick(float DeltaTime);

  void ApplyForce(const Vec2& Force) {
    Acceleration += Force / Mass;
  }

  const Vec2& GetPosition() const {
    return Position;
  }

  void Render(SDL_Surface* Surface);

 private:
  float ForceTimeRemaining{5.0f};
  float DragCoefficient{0.2f};
  Vec2 GetDragForce() const {
    return -Velocity * Velocity.GetLength()
      * DragCoefficient;
  }

  float GetFrictionCoefficient() const {
    if (Position.y < 200) {
      // Object isn't on the ground
      return 0;
    }
    return 0.5f;
  }

  Vec2 GetFrictionForce(float DeltaTime) const {
    float MaxMagnitude{GetFrictionCoefficient()
      * Mass * Acceleration.y};

    if (MaxMagnitude <= 0) return Vec2{0, 0};

    float StoppingMagnitude{Mass *
      Velocity.GetLength() / DeltaTime};

    return -Velocity.Normalize() * std::min(
      MaxMagnitude, StoppingMagnitude);
  }

  void Clamp(Vec2& V) const {
    V.x = std::abs(V.x) > 0.1f ? V.x : 0.0f;
    V.y = std::abs(V.y) > 0.1f ? V.y : 0.0f;
  }

  Vec2 Acceleration{0, 9.8f * PIXELS_PER_METER};
  float Mass{50.0f};
  Vec2 Position{0, 0};
  Vec2 Velocity{0, 0};
  Image ImageClass;
  const Scene& SceneClass;

  void ApplyImpulse(const Vec2& Impulse) {
    Velocity += Impulse / Mass;
  } 

  void CalculateAnimation();
  void ApplyPositionalImpulse(const Vec2& Origin, float Magnitude) {
    Vec2 Displacement{GetPosition() - Origin};
    Vec2 Direction{Displacement.Normalize()};
    float DistancePixels{Displacement.GetLength()};
    float DistanceMeters(DistancePixels / PIXELS_PER_METER);

    // Apply inverse-square law with a small offset to prevent
    // extreme forces
    float AdjustmentMagnitude{
      Magnitude / ((DistanceMeters + 0.1f) * (DistanceMeters + 0.1f))
    };

    ApplyImpulse(Direction * AdjustmentMagnitude);
  }
  BoundingBox Bounds;
}; 
