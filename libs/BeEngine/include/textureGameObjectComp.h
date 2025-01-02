#pragma once

#include "SDL.h"
#include "brush.h"
#include "gameObjectComponent.h"

DEFINE_GAMEOBJECTCOMP_START(TextureGameObjectComp);
TextureBrush textureBrush;
DEFINE_GAMEOBJECTCOMP_END(TextureGameObjectComp);

void textureGameObjectComp_changeTexture(TextureGameObjectComp *comp, char *texturePath);