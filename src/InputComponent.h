#pragma once
#include <functional>
#include <memory>
#include <unordered_map>
#include "Component.h"

class Command;
using CommandPtr = std::unique_ptr<Command>;

// Command factories take no args and return
// CommandPtr (std::unique_ptr<Command>)
using CommandFactory = std::function<CommandPtr()>;
using KeyToFactoryMap = std::unordered_map<SDL_Keycode, CommandFactory>;

class InputComponent : public Component {
  public:
    using Component::Component;
    void Initialize() override;
    void Tick(float DeltaTime) override;

    void HandleEvent(const SDL_Event& E) override;

    void BindKeyDown(SDL_Keycode Key, CommandFactory Factory) {
      KeyDownBindings[Key] = Factory;
    }

    void BindKeyHeld(SDL_Keycode Key, CommandFactory Factory) {
      KeyHeldBindings[Key] = Factory;
    }

  private:
    KeyToFactoryMap KeyDownBindings;
    KeyToFactoryMap KeyHeldBindings;
};
