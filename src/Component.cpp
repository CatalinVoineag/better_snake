#include "Component.h"
#include "Scene.h"
#include "Entity.h"

Scene& Component::GetScene() const {
  return GetOwner()->GetScene();
}

AssetManager& Component::GetAssetManager() const {
  return GetScene().GetAssetManager();
}

Vec2 Component::GetOwnerPosition() const {
  TransformComponent* Transform{
    GetOwner()->GetTransformComponent()
  };
  if (!Transform) {
    std::cerr << "Can't find owner position";
    return {0, 0};
  }

  return Transform->GetPosition();
}
