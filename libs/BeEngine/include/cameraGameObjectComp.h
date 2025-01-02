#pragma once

#include "SDL.h"
#include "gameObjectComponent.h"
#include "vector2.h"

DEFINE_GAMEOBJECTCOMP_START(CameraGameObjectComp);
Vector2 _viewportBounds;
Vector2 _viewportWorldLocation;
DEFINE_GAMEOBJECTCOMP_END(CameraGameObjectComp);