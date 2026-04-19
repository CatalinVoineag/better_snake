#pragma once
#include <iostream>
#include <string>
#include <memory>
#include <SDL3/SDL.h>
#include "Component.h"

class ImageComponent : public Component {
  public:
    using Component::Component;

    ImageComponent(Entity* Owner, const std::string& FilePath);

    void Initialize() override;
    void Render(SDL_Surface* Surface) override;

    bool LoadNewImage(const std::string& NewPath);

  private:
    std::shared_ptr<SDL_Surface> ImageSurface{nullptr};
    std::string ImageFilePath;
};
