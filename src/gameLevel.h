#pragma once

#include "level.h"

DEFINE_LEVEL(GameLevel);

void windowResized(Vector2* newSize);
void event_ballCollision_beginOverlap(GameObject* self, GameObject* collidedWith);
void event_anyInput(SDL_Event* event);