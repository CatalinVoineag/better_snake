#pragma once
#include "Vec2.h"

class Character {
  public:
  Vec2 Position{5, 1};
  float MovementSpeed {3.0};

  void Move(const Vec2& Movement) {
    if (Movement.GetLength() <= MovementSpeed) {
      Position += Movement;
      return;
    }
    Vec2 Direction{Movement.Normalize()};
    Vec2 ConstrainedMovement{Direction * MovementSpeed};
    Position += ConstrainedMovement;
  }

  void MoveTowards(const Character& Target) {
    Move(Target.Position - Position);
  }

  void MoveAway(const Character& Target) {
    Move(Position - Target.Position);
  }
};
