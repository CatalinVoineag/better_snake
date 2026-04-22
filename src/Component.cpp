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

void Component::SetOwnerPosition(const Vec2& Pos) const {
  TransformComponent* Transform{
    GetOwner()->GetTransformComponent()
  };

  if (!Transform) {
    std::cerr << "Error, attempted to set position on entity with no transform component\n";
  } else {
    Transform->SetPosition(Pos);
  }
}

float Component::GetOwnerScale() const {
  TransformComponent* Transform{GetOwner()->GetTransformComponent()};

  if (!Transform) {
    std::cerr << "Error: attempted to get scale of an entity with no transform component\n";
    return 1.0;
  }

  return Transform->GetScale();
}
