#include <iostream> 
#include <SDL3/SDL.h> 
#include <memory> 
#include "InputComponent.h"
#include "Entity.h"
#include "TransformComponent.h"
#include "Commands.h"
#include "Vec2.h"
#include "Scene.h"

namespace {
  // Define movement speed
  const float SPEED{5.f * Scene::PIXELS_PER_METER};
  // Factory function for moving left (negative X)
  CommandPtr CreateMoveLeftCommand() {
    return std::make_unique<MovementCommand>(
      Vec2{-SPEED, 0.0}
    );
  }

  // Factory function for moving right (positive X)
  CommandPtr CreateMoveRightCommand() {
    return std::make_unique<MovementCommand>(
      Vec2{SPEED, 0.0}
    );
  }

  CommandPtr CreateJumpCommand() {
    // Example value in kg*m/s
    const float JUMP_IMPULSE_MAGNITUDE{
      -500.f * Scene::PIXELS_PER_METER
    };

    // Return a jump command instead of movement
    return std::make_unique<JumpCommand>(
      Vec2{0.0, JUMP_IMPULSE_MAGNITUDE}
    );
  }
}

void InputComponent::Initialize() {
  BindKeyHeld(SDLK_LEFT, CreateMoveLeftCommand);
  BindKeyHeld(SDLK_RIGHT, CreateMoveRightCommand);
  BindKeyHeld(SDLK_SPACE, CreateJumpCommand);
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
