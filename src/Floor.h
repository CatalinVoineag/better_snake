#pragma once
#include "Entity.h"
#include "Scene.h"

class Floor : public Entity {
  public:
    Floor(Scene& Scene) : Entity{Scene} {
      AddTransformComponent()->SetPosition({
        4.5f * Scene.PIXELS_PER_METER,
        13.f * Scene.PIXELS_PER_METER
      });
      AddImageComponent("floor.png");
      AddCollisionComponent()->SetSize(
        5.0f * Scene.PIXELS_PER_METER,
        2.0f * Scene.PIXELS_PER_METER
      );
    }
};
