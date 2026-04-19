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
  Scene() {
    EntityPtr& Player{
      Entities.emplace_back(std::make_unique<Entity>(*this))
    };

    Player->AddTransformComponent();
    Player->AddTransformComponent()->SetPosition({100, 240});
    Player->AddInputComponent();
    Player->AddImageComponent("apple.png");

    EntityPtr& Enemy{Entities.emplace_back(std::make_unique<Entity>(*this))};
    Enemy->AddTransformComponent()->SetPosition({250, 20});
    Enemy->AddImageComponent("dwarf.png");
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
  AssetManager Assets;
  EntityPtrs Entities;
};
