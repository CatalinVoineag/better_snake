#pragma once
#include <SDL3/SDL_pixels.h>
#include <iostream>
#include <SDL3/SDL.h>
#include "Utilities.h"
#include "Vec2.h"
#include "Component.h"

class TransformComponent : public Component {
  public:
    using Component::Component;

    void Tick(float DeltaTime) override {
    }

    Vec2 GetPosition() const {
      return Position;
    }

    void SetPosition(const Vec2& NewPosition) {
      Position = NewPosition;
    }

    float GetScale() const { return Scale; }
    void SetScale(float NewScale) {
      Scale = NewScale;
    }

    void DrawDebugHelpers(SDL_Surface* S) override {
      auto [x, y]{GetPosition()};
      SDL_Rect Square{Utilities::Round({x - 10, y - 10, 20, 20})};

      SDL_FillSurfaceRect(
        S,
        &Square,
        SDL_MapRGB(
          SDL_GetPixelFormatDetails(S->format),
          nullptr, 255, 0, 0
        )
      );
    }

    void Move(const Vec2& Movement) {
      Position += Movement;
    }

  private:
    Vec2 Position{0, 0};
    float Scale{1.0};
};
