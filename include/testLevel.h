#pragma once

#include "level.h"

DEFINE_LEVEL(testLevel);

void drawTest(GameObject *gameObject);
void event_gameEngineInitialized();
void event_tick();
void event_draw();
void _event_anyInput(SDL_Event *event);
void event_beginOverlap(GameObject *self, GameObject *collidedWith);
void event_endOverlap(GameObject *self, GameObject *collidedWith);