#include <iostream>
#include "ImageComponent.h" 
#include "Entity.h"
#include "TransformComponent.h"

void ImageComponent::Initialize() {
  Entity* Owner{GetOwner()};

  if (!Owner->GetTransformComponent()) {
    std::cout << "Error: ImageComponent requires TransofrmComponent on its owner\n";

    Owner->RemoveComponent(this);
  }
}

void ImageComponent::Render(SDL_Surface* Surface) {
  TransformComponent* Transform{
    GetOwner()->GetTransformComponent()
  };

  std::cout << "ImageComponent rendering at: "
    << Transform->GetPosition() << '\n';
}
