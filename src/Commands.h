#pragma once
#include "Vec2.h"

class Entity;

class Command {
  public:
    virtual void Execute(Entity* Target) {};
    virtual ~Command() = default;
};

class MovementCommand : public Command {
  public:
    MovementCommand(Vec2 Movement) : Movement{Movement} {}
    void Execute(Entity* T);
    void Undo();

    Entity* Target;
    Vec2 Movement;
};
