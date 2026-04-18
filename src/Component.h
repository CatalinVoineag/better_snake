#pragma once
#include <SDL3/SDL.h>

class Entity;

class Component {
  public:
    Component(Entity* Owner) : Owner(Owner) {}

    virtual void Initialize() {}
    virtual void HandleEvent(const SDL_Event& E) {}
    virtual void Tick(float DeltaTime) {}
    virtual void Render(SDL_Surface* Surface) {}
    virtual ~Component() = default;

    Entity* GetOwner() const {
      return Owner;
    }

  private:
    Entity* Owner{nullptr};
};
