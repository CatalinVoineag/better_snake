#pragma once
#include <SDL3/SDL.h>
#include <memory>
#include <vector>
#include <string>
#include <ranges>
#include "Entity.h"
#include "AssetManager.h"

using EntityPtr = std::unique_ptr<Entity>;
using EntityPtrs = std::vector<EntityPtr>;

class Scene {
public:
  static inline int PIXELS_PER_METER{50};
  static inline Vec2 GRAVITY{0, static_cast<float>(9.8 * PIXELS_PER_METER)};

#ifdef DRAW_DEBUG_HELPERS
    SDL_Surface* Trajectories{
      SDL_CreateSurface(
        700, 500, SDL_PIXELFORMAT_RGBA32
      )
    };
#endif
  
  Scene();

  // Public access to the Asset Manger if needed somewhere
  AssetManager& GetAssetManager() {
    return Assets;
  }

  void HandleEvent(const SDL_Event& E) {
    for (EntityPtr& Entity : Entities) {
      Entity->HandleEvent(E);
    }
  }
  
  void Tick(float DeltaTime) {
    // Tick all entities, update physics, collision bounds, etc
    for (EntityPtr& Entity : Entities) {
      Entity->Tick(DeltaTime);
    }

    // Check for collisions between entities 
    CheckCollisions();
  }

  void Render(SDL_Surface* Surface) {
    for (EntityPtr& Entity : Entities) {
      Entity->Render(Surface);
    }

#ifdef DRAW_DEBUG_HELPERS
    SDL_BlitSurface(
      Trajectories, nullptr, Surface, nullptr
    );
#endif
  }
private:
  AssetManager Assets;
  EntityPtrs Entities;
  void CheckCollisions();
};
