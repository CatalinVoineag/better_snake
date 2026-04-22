#pragma once
#include <iostream>
#include <string>
#include <memory>
#include <optional>
#include <SDL3/SDL.h>
#include "Component.h"
#include "Vec2.h"

enum class ScalingMode {None, Fill, Contain, Cover};

class ImageComponent : public Component {
  public:
    using Component::Component;

    ImageComponent(Entity* Owner, const std::string& FilePath);

    void Initialize() override;
    void Render(SDL_Surface* Surface) override;

    void SetWidth(float NewWidth);
    void SetHeight(float NewHeight);
    void ResetWidth();
    void ResetHeight();
    float GetWidth() const;
    float GetHeight() const;
    void SetScalingMode(ScalingMode Mode);

    bool LoadNewImage(const std::string& NewPath);

    void SetOffset(const Vec2& NewOffset) {
      Offset = NewOffset;
    } 

    int GetSurfaceWidth() const;
    int GetSurfaceHeight() const;

    void DrawDebugHelpers(SDL_Surface*) override;

  private:
    std::shared_ptr<SDL_Surface> ImageSurface{nullptr};
    std::string ImageFilePath;
    Vec2 Offset{0, 0};
    std::optional<float> Width{std::nullopt};  
    std::optional<float> Height{std::nullopt};
    ScalingMode ScaleMode{ScalingMode::Fill};
};
