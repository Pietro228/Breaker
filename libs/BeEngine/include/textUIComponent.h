#pragma once

#include "font.h"
#include "uiCanvas.h"
#include "uiComponent.h"

DEFINE_UICOMPONENT_START(TextUIComponent);
char text[256];
Font font;
SDL_Surface *_textSurface;
SDL_Texture *_textTexture;
DEFINE_UICOMPONENT_END(TextUIComponent);
