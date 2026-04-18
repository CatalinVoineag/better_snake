#pragma once
#include <iostream>
#include "Component.h"

class ImageComponent : public Component {
  public:
    using Component::Component;

    void Initialize() override;
    void Render(SDL_Surface* Surface) override;
};
