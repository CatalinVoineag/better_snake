#pragma once
#include <iostream>
#include "Vec2.h"
#include "Component.h"

class TransformComponent : public Component {
  public:
    using Component::Component;

    void Tick(float DeltaTime) override {
      std::cout << "TransformComponent ticking\n";
    }

    Vec2 GetPosition() const {
      return Position;
    }

  private:
    Vec2 Position{0, 0};
};
