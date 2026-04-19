#pragma once
#include <iostream>
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

    void Move(const Vec2& Movement) {
      Position += Movement;
    }

  private:
    Vec2 Position{0, 0};
};
