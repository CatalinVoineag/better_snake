#pragma once
#include "Entity.h"
#include "Scene.h"
#include "Floor.h"

class Character : public Entity {
  public:
    Character(Scene& Scene) : Entity{Scene} {
      AddTransformComponent()->SetPosition({
        6.f * Scene.PIXELS_PER_METER,
        5.f * Scene.PIXELS_PER_METER
      });
      AddPhysicsComponent()->SetMass(50.0);
      AddImageComponent("apple.png");
      AddCollisionComponent()->SetSize(
        1.9f * Scene.PIXELS_PER_METER,
        1.7f * Scene.PIXELS_PER_METER
      );
    }

    void HandleCollision(Entity& Other) override {
      // Check if we collided with a floor
      Floor* FloorPtr{dynamic_cast<Floor*>(&Other)};

      if (!FloorPtr) return;

      CollisionComponent* MyCollider{
        GetCollisionComponent()
      };
      CollisionComponent* FloorCollider{
        FloorPtr->GetCollisionComponent()
      };

      SDL_FRect Intersection;
      MyCollider->GetCollisionRectangle(*FloorCollider, &Intersection);

      Vec2 CurrentPos{GetTransformComponent()->GetPosition()};
      GetTransformComponent()->SetPosition({
        CurrentPos.x,
        CurrentPos.y - Intersection.h
      });

      PhysicsComponent* Physics{GetPhysicsComponent()};
      if (Physics) {
        Vec2 CurrentVel{Physics->GetVelocity()};
        // Stop vertical movement upon landing
        if (CurrentVel.y < 0) { // only if failing
          Physics->SetVelocity({CurrentVel.x, 0.0});
        }
      }
    }
};
