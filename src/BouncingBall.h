#pragma once
#include "Entity.h"
#include "Scene.h"

class BouncingBall : public Entity {
  public:
    BouncingBall(Scene& Scene) : Entity{Scene} {
      AddTransformComponent()->SetPosition({
        5.f * Scene.PIXELS_PER_METER,
        2.f * Scene.PIXELS_PER_METER
      });
      AddPhysicsComponent()->SetVelocity({
        5.f * Scene.PIXELS_PER_METER,
        -3.f * Scene.PIXELS_PER_METER
      });
      AddImageComponent("ball.png");
      AddCollisionComponent();
    }

    void HandleCollision(Entity& Other) override {
      SDL_FRect Intersection;

      GetCollisionComponent()->GetCollisionRectangle(
        *Other.GetCollisionComponent(), &Intersection
      );

      PhysicsComponent* Physics{GetPhysicsComponent()};

      TransformComponent* Transform{GetTransformComponent()};

      // Safety check - we need these to bound
      if (!(Physics && Transform)) return;

      Vec2 CurrentPos{Transform->GetPosition()};
      if (Intersection.w < Intersection.h) {
        if (Physics->GetVelocity().x > 0)
          CurrentPos.x -= Intersection.w;
        else
          CurrentPos.x += Intersection.w;
      } else {
        if (Physics->GetVelocity().y <0)
          CurrentPos.y += Intersection.h;
        else
          CurrentPos.y -= Intersection.h;
      }
      Transform->SetPosition(CurrentPos);
    }
};
