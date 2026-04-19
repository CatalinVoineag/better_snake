#include <iostream>
#include "ImageComponent.h" 
#include "TransformComponent.h" 
#include "Entity.h" 
#include "AssetManager.h" 

void ImageComponent::Initialize() {
  Entity* Owner{GetOwner()};
  if (!Owner->GetTransformComponent()) {
    std::cout << "Error: ImageComponent requires"
      " TransformComponent on its Owner\n";

    // Request removal
    Owner->RemoveComponent(this);
  }
}

ImageComponent::ImageComponent(
  Entity* Owner,
  const std::string& FilePath
) : Component(Owner), ImageFilePath(FilePath) {
  // Load the image from the file path 
  ImageSurface = GetAssetManager().LoadSurface(ImageFilePath);

  // Check if IMG_Load returned a valid surface pointer
  if (!ImageSurface) {
    // If null, loading failed. Print an error.
    std::cerr << "Failed to load image: " << FilePath << " Error " << SDL_GetError() << '\n';
  } else {
    // Loading succeeded!
    std::cout << "Loaded image: " << FilePath << '\n';
  }
}

void ImageComponent::Render(SDL_Surface* Surface) {
  // only proceed if we have a surface loaded
  if (!ImageSurface) return;

  // Check for transform component (needed for position)
  TransformComponent* Transform{GetOwner()->GetTransformComponent()};

  if (Transform) {
    // std::cout << "ImageComponent (" << ImageFilePath << ") reado to be render at: " << Transform->GetPosition() << '\n';
  } else {
    std::cout << "ImageComponent (" << ImageFilePath << ") ready, but no Transofrm component found\n";
  }
}

bool ImageComponent::LoadNewImage(const std::string& NewPath) {
  ImageFilePath = NewPath;
  ImageSurface = GetAssetManager().LoadSurface(NewPath);

  return ImageSurface != nullptr;
}

