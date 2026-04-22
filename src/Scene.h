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
  
  Scene() {
    EntityPtr& Player{
      Entities.emplace_back(std::make_unique<Entity>(*this))
    };

    Player->AddTransformComponent()->SetPosition({300, 440});
    Player->AddInputComponent();
    Player->GetTransformComponent()->SetScale(0.25);
    ImageComponent* PlayerImage{
      Player->AddImageComponent("apple.png")
    };

    PlayerImage->SetOffset({
      PlayerImage->GetSurfaceWidth() * -0.5f,
      PlayerImage->GetSurfaceHeight() * -0.5f
    });
    // Add physics
    PhysicsComponent* Physics{
      Player->AddPhysicsComponent()
    };
    Physics->SetMass(50);
    Physics->SetVelocity({
      5.f * PIXELS_PER_METER, -7.f * PIXELS_PER_METER
    });
    // don't know the exact size of image
    Player->AddCollisionComponent()->SetSize(
      1.9f * PIXELS_PER_METER, 
      1.7f * PIXELS_PER_METER
    );

    // --- Static Entity ---
    EntityPtr& Floor{Entities.emplace_back(
      std::make_unique<Entity>(*this)
    )};

    Floor->AddTransformComponent()
      ->SetPosition({
        1.f * PIXELS_PER_METER,
        4.f * PIXELS_PER_METER,
      });
    // Add an image - optional - we can see where the
    // the object is based on the collision component
    // drawn by DrawDebugHelpers()
    Floor->AddImageComponent("floor.png");
    Floor
      ->AddCollisionComponent()
      ->SetSize(
        5.0f * PIXELS_PER_METER,
        2.0f * PIXELS_PER_METER
      );


    // EntityPtr& Enemy{Entities.emplace_back(std::make_unique<Entity>(*this))};
    // Enemy->AddTransformComponent()->SetPosition({250, 20});
    // Enemy->GetTransformComponent()->SetScale(2.5);
    // ImageComponent* EnemyImage {
    //   Enemy->AddImageComponent("dwarf.png")
    // };
    // EnemyImage->SetWidth(150);
    // EnemyImage->SetHeight(150);
    // EnemyImage->SetScalingMode(ScalingMode::Cover);
  }

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
