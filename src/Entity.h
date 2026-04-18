#pragma once
#include <memory>
#include <vector>
#include <ranges>
#include <SDL3/SDL.h>
#include "Component.h"
#include "TransformComponent.h"
#include "ImageComponent.h"

using ComponentPtr = std::unique_ptr<Component>;
using ComponentPtrs = std::vector<ComponentPtr>;

class Entity {
  public:
    virtual void HandleEvent(const SDL_Event& E) {
      for (ComponentPtr& C : Components) {
        C->HandleEvent(E);
      }
    }

    virtual void Tick(float DeltaTime) {
      for (ComponentPtr& C : Components) {
        C->Tick(DeltaTime);
      }
    }

    virtual void Render(SDL_Surface* Surface) {
      for (ComponentPtr& C : Components) {
        C->Render(Surface);
      }
    }

    virtual ~Entity() = default;

    TransformComponent* AddTransformComponent() {
      if (GetTransformComponent()) {
        std::cout << "Error: Cannot have multiple transform components";
        return nullptr;
      }
      ComponentPtr& NewComponent{
        Components.emplace_back(std::make_unique<TransformComponent>(this))
      };

      NewComponent->Initialize();

      return static_cast<TransformComponent*>(NewComponent.get());
    }

    TransformComponent* GetTransformComponent() const {
      for (const ComponentPtr& C : Components) {
        if (auto Ptr{dynamic_cast<TransformComponent*>(C.get())}) {
          return Ptr;
        }
      }

      return nullptr;
    }

    void RemoveComponent(Component* PtrToRemove) {
      for (size_t i{0}; i < Components.size(); i++) {
        if (Components[i].get() == PtrToRemove) {
          Components.erase(Components.begin() + i);
          return;
        }
      }

      std::cout << "Component not found\n";
    }

    ImageComponent* AddImageComponent() {
      ComponentPtr& NewComponent{
        Components.emplace_back(
          std::make_unique<ImageComponent>(this)
        )
      };

      NewComponent->Initialize();

      return static_cast<ImageComponent*>(
        NewComponent.get()
      );
    }

    auto GetImageComponents() {
      auto ToImagePtr{[](const ComponentPtr& C) {
        return dynamic_cast<ImageComponent*>(C.get());
      }};

      auto IsNotNull{[](ImageComponent* Ptr){
        return Ptr != nullptr;
      }};
      
      return Components | std::views::transform(ToImagePtr) | std::views::filter(IsNotNull);
    }

  private:
    ComponentPtrs Components;
};
