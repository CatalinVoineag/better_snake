#include "Commands.h"
#include "Entity.h"
#include "TransformComponent.h"

void MovementCommand::Execute(Entity* T) {
  Target = T;
  std::cout << "\nMoving: " << Movement;
  Target->GetTransformComponent()->Move(Movement);
}

void MovementCommand::Undo() {
  Target->GetTransformComponent()->Move(-Movement);
}
