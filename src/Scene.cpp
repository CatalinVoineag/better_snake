#include <vector>
#include <iostream>
#include "Scene.h"
#include "CollisionComponent.h"
#include "Floor.h"
#include "Character.h"
#include "BouncingBall.h"

using EntityPtr = std::unique_ptr<Entity>;
using EntityPtrs = std::vector<EntityPtr>;

Scene::Scene() {
  // Entities.emplace_back(std::make_unique<Character>(*this));
  // Entities.emplace_back(std::make_unique<Floor>(*this));
  Entities.emplace_back(std::make_unique<BouncingBall>(*this));

  EntityPtr& WallA{Entities.emplace_back(
    std::make_unique<Entity>(*this)
  )};
  WallA->AddTransformComponent()
    ->SetPosition({
      10.f * PIXELS_PER_METER,
      1.f * PIXELS_PER_METER
    });
  WallA->AddCollisionComponent()
    ->SetSize(
      2.f * PIXELS_PER_METER,
      5.f * PIXELS_PER_METER
    );

  EntityPtr& WallB{Entities.emplace_back(
    std::make_unique<Entity>(*this)
  )};
  WallB->AddTransformComponent()
    ->SetPosition({
      4.5f * PIXELS_PER_METER,
      5.f * PIXELS_PER_METER
    });
  WallB->AddCollisionComponent()
    ->SetSize(
      5.0f * PIXELS_PER_METER,
      2.0f * PIXELS_PER_METER
    );
}

void Scene::CheckCollisions() {
  // Basic n^2 check is inefficient for large scenes
  for (size_t i{0}; i < Entities.size(); i++) {
    CollisionComponent* ColA {Entities[i]->GetCollisionComponent()};

    // Skip if no collision component
    if (!ColA) continue;

    for (size_t j{i+1}; j < Entities.size(); j++) {
      CollisionComponent* ColB{Entities[j]->GetCollisionComponent()};
      // Skip if no collision component
      if (!ColB) continue;

      if (ColA->IsCollidingWith(*ColB)) {
        Entities[i]->HandleCollision(*Entities[j]);
        Entities[j]->HandleCollision(*Entities[i]);
      }
    };
  }
}

