#include <SDL3/SDL.h>
#include "GameObject.h"

void GameObject::Render(SDL_Surface* Surface) {
  ImageClass.Render(Surface, Position);
}
