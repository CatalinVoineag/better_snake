#pragma once
#include <memory>
#include <vector>
#include <ranges>
#include <SDL3/SDL.h>
#include "Component.h"
#include "TransformComponent.h"
#include "ImageComponent.h"
#include "InputComponent.h"
#include "Commands.h"

using ComponentPtr = std::unique_ptr<Component>;
using ComponentPtrs = std::vector<ComponentPtr>;

class Scene;

class Entity {
  public:
    Entity(Scene& Scene) : OwningScene{Scene} {}
    Scene& GetScene() const { return OwningScene; }

    virtual void HandleEvent(const SDL_Event& E) {
      for (ComponentPtr& C : Components) {
        C->HandleEvent(E);
      }
    }

    virtual void HandleCommand(std::unique_ptr<Command> Cmd) {
      Cmd->Execute(this);
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

    ImageComponent* AddImageComponent(const std::string& FilePath) {
      ComponentPtr& NewComponent{
        Components.emplace_back(
          std::make_unique<ImageComponent>(this, FilePath)
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

    InputComponent* AddInputComponent() {
      if (GetInputComponent()) {
        std::cout << "Error: Cannot have multiple input components\n";
        return nullptr;
      }

      std::unique_ptr<Component>& NewComponent{
        Components.emplace_back(std::make_unique<InputComponent>(this))
      };

      NewComponent->Initialize();

      return static_cast<InputComponent*>(NewComponent.get());
    }

    InputComponent* GetInputComponent() const {
      for (const ComponentPtr& C : Components) {
        if (auto Ptr{dynamic_cast<InputComponent*>(C.get())}) {
          return Ptr;
        }
      }
      return nullptr;
    }

  private:
    Scene& OwningScene;
    ComponentPtrs Components;
};
