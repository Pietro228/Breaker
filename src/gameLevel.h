#pragma once

#include "level.h"

DEFINE_LEVEL(GameLevel);

void windowResized(Vector2* newSize);
void event_ballCollision_hit(GameObject* self, GameObject* collidedWith, Vector2* normal);
void event_anyInput(SDL_Event* event);