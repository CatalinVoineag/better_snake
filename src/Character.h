#pragma once
#include <iostream>
#include "Entity.h"
#include "ImageComponent.h"
#include "TransformComponent.h"

class Character : public Entity {
  public:
    Character() {
      Transform = AddTransformComponent();
      // Image = AddImageComponent();
    }

    void SayHello() const {
      std::cout << "Hello from character\n";
    }

  private: 
    TransformComponent* Transform{nullptr};
    ImageComponent* Image{nullptr};
};
