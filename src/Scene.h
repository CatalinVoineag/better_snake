#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include <ranges>
#include "Entity.h"
#include "Character.h"

using EntityPtr = std::unique_ptr<Entity>;
using EntityPtrs = std::vector<EntityPtr>;

class Scene {
public:
  Scene() {
    EntityPtr& NewEntity{Entities.emplace_back(
      std::make_unique<Entity>()
    )};
    NewEntity->AddImageComponent();
    NewEntity->AddImageComponent();
    NewEntity->AddImageComponent();

    std::cout << "ImageComponent Count: " << std::ranges::distance(NewEntity->GetImageComponents());

    for (ImageComponent* C : NewEntity->GetImageComponents()) {
      std::cout << "\n Doing something with a image component\n";
    }


    EntityPtr& NewCharacter{Entities.emplace_back(std::make_unique<Character>())};
  }
  void HandleEvent(const SDL_Event& E) {
    for (EntityPtr& Entity : Entities) {
      Entity->HandleEvent(E);
    }
  }
  
  void Tick(float DeltaTime) {
    for (EntityPtr& Entity : Entities) {
      Entity->Tick(DeltaTime);
    }
  }

  void Render(SDL_Surface* Surface) {
    for (EntityPtr& Entity : Entities) {
      Entity->Render(Surface);
    }
  }
private:
  EntityPtrs Entities;
};
