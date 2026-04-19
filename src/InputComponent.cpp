#include <iostream> 
#include <SDL3/SDL.h> 
#include <memory> 
#include "InputComponent.h"
#include "Entity.h"
#include "TransformComponent.h"
#include "Commands.h"
#include "Vec2.h"

namespace {
  // Factory function for moving left (negative X)
  CommandPtr CreateMoveLeftCommand() {
    return std::make_unique<MovementCommand>(Vec2{-5.0, 0.0});
  }

  // Factory function for moving right (positive X)
  CommandPtr CreateMoveRightCommand() {
    return std::make_unique<MovementCommand>(Vec2{5.0, 0.0});
  }
}

void InputComponent::Initialize() {
  BindKeyHeld(SDLK_LEFT, CreateMoveLeftCommand);
  BindKeyHeld(SDLK_RIGHT, CreateMoveRightCommand);
}

void InputComponent::Tick(float DeltaTime) {
  Entity* Owner{GetOwner()};
  if (!Owner) return;

  // Get the current keyboard state
  const bool* CurrentKeyStates{SDL_GetKeyboardState(nullptr)};

  // Check bindings for keys being held down
  for (const auto& [Key, Factory] : KeyHeldBindings) {
    SDL_Scancode Scancode{
      SDL_GetScancodeFromKey(Key, nullptr)
    };

    if (CurrentKeyStates[Scancode]) {
      // Key is held, create and handle command
      Owner->HandleCommand(Factory());
    }
  }
}

void InputComponent::HandleEvent(const SDL_Event& E) {
  if (E.type == SDL_EVENT_KEY_DOWN) {
    Entity* Owner{GetOwner()};
    if (!Owner) return;

    SDL_Keycode Key{E.key.key};
    if (KeyDownBindings.contains(Key)) {
      Owner->HandleCommand(KeyDownBindings[Key]());
    }
  }
}
