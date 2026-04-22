#include <iostream>
#include <cmath>
#include "CollisionComponent.h"
#include "Entity.h"
#include "Utilities.h"

void CollisionComponent::Initialize() {
  if (!GetOwner()->GetTransformComponent()) {
    std::cerr << "Error: Collision component requires transform component\n";
    GetOwner()->RemoveComponent(this);
  }
}

void CollisionComponent::SetOffset(const Vec2& NewOffset) {
  Offset = NewOffset;
  // Bounds will be recalculated in Tick()
}

void CollisionComponent::SetSize(float NewWidth, float NewHeight) {
  if (NewWidth < 0 || NewHeight < 0) {
    std::cerr << "Warning: CollisionComponent width or height cannot be negative. Using absolut values\n";
    Width = std::abs(NewWidth);
    Height = std::abs(NewHeight);
  } else {
    Width = NewWidth;
    Height = NewHeight;
  }
}

const SDL_FRect& CollisionComponent::GetBounds() const {
  return Bounds;
}

void CollisionComponent::Tick(float DeltaTime) {
  Vec2 OwnerPos{GetOwnerPosition()};
  float OwnerScale{GetOwnerScale()};

  // Calculate position and dimensions
  Bounds.x = OwnerPos.x + Offset.x;
  Bounds.y = OwnerPos.y + Offset.y;
  Bounds.w = Width + OwnerScale;
  Bounds.h = Height + OwnerScale;
}

bool CollisionComponent::IsCollidingWith(const CollisionComponent& Other) const {
  return SDL_HasRectIntersectionFloat(&Bounds, &Other.Bounds);
}

bool CollisionComponent::GetCollisionRectangle(
  const CollisionComponent& Other,
  SDL_FRect* OutIntersection
) const {
  if (!OutIntersection) {
    std::cerr << "Error: OutIntersection pointer is null\n";
    return false;
  }

  return SDL_GetRectIntersectionFloat(
    &Bounds, &Other.Bounds, OutIntersection
  );
}

void CollisionComponent::DrawDebugHelpers(SDL_Surface* Surface) {
  // Convert bounds to integer SDL_Rect for drawing
  SDL_Rect ScreenBounds{Utilities::Round(Bounds)};

  // Draw outline using the helper
  Utilities::DrawRectOutline(
    Surface,
    ScreenBounds,
    // Yellow
    SDL_MapRGB(
      SDL_GetPixelFormatDetails(Surface->format),
      nullptr, 255, 255, 0
    ),
    1 // thin line
  );
};
