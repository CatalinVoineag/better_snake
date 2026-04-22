#include <iostream>
#include "PhysicsComponent.h"
#include "Scene.h"
#include "Entity.h"
#include "Utilities.h"

void PhysicsComponent::Initialize() {
  // Physics needs a Transform to know where the entity is
  if (!GetOwner()->GetTransformComponent()) {
    std::cerr << "Error: PhysicsComponent requires transform component on it's owner\n";
    GetOwner()->RemoveComponent(this);
  }
}

void PhysicsComponent::SetMass(float NewMass) {
  if (NewMass <= 0.0) {
    std::cerr << "Error: Mass must be positive, setting to 1kg\n";
    Mass = 1.0;
  } else {
    Mass = NewMass;
  } 
}

void PhysicsComponent::ApplyForce(const Vec2& Force) {
  // A = F/M
  if (Mass > 0.0f) {
    Acceleration += Force / Mass;
  }
}

void PhysicsComponent::ApplyImpulse(const Vec2& Impulse) {
  if (Mass > 0.0f) {
    Velocity += Impulse / Mass;
  }
}

void PhysicsComponent::Tick(float DeltaTime) {
  // Apply persistent forces like gravity
  ApplyForce(Scene::GRAVITY * Mass);
  // Update velocity based on Acceleration
  Velocity += Acceleration * DeltaTime;

  // Update position based on velocity
  // get current position, add velocity
  // and set new position
  SetOwnerPosition(
    GetOwnerPosition() + Velocity * DeltaTime
  );

  // Reset Acceleration for the next frame
  // forces applied before the next tick will accumulate here
  Acceleration = {0.0, 0.0};
  // Reset horizontal velocity for every frame
  Velocity.x = 0;
}

void PhysicsComponent::DrawDebugHelpers(SDL_Surface* Surface) {
#ifdef DRAW_DEBUG_HELPERS
  auto [x, y]{GetOwnerPosition()};
  SDL_Rect PositionIndicator{int(x) - 2, int(y) - 2, 4, 4};

  SDL_FillSurfaceRect(
    GetScene().Trajectories,
    &PositionIndicator,
    SDL_MapRGB(
      SDL_GetPixelFormatDetails(GetScene().Trajectories->format),
      nullptr, 0, 0, 255
    )
  );
#endif
}
