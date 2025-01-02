#ifndef _PHYSICSENGINE_H_
#define _PHYSICSENGINE_H_

#include "gameObject.h"

void _physicsEngine_tick();
int physicsEngine_doesGameObjectCollide(GameObject* gameObject);

#endif