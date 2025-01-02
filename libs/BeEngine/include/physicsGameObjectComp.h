#pragma once

#include "gameObjectComponent.h"
/**
 * @brief Physics component for game objects
 *
 * bounciness = Multiplies velocity on impact
 */
DEFINE_GAMEOBJECTCOMP_START(PhysicsGameObjectComp);
// Custom variables
int bounce;
float bounciness;
DEFINE_GAMEOBJECTCOMP_END(PhysicsGameObjectComp);