#include <vector>
#include <iostream>
#include "Scene.h"
#include "CollisionComponent.h"

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
        std::cout << "Colision detected \n";
      }
    };
  }
}

