#pragma once

#include <sys/time.h>

#include "brush.h"
#include "font.h"
#include "uiCanvas.h"
#include "uiComponent.h"

DEFINE_UICOMPONENT_START(TextBoxUIComponent);
// Custom variables
// TODO: Text alignment
char text[256];
Font font;
Thickness padding;
TextureBrush backgroundBrush;
BorderBrush borderBrush;
BorderBrush focusedBorderBrush;
SDL_Surface *_textSurface;
SDL_Texture *_textTexture;
char _lastText[256];
int _lastSize;
struct timeval _lastTimeTyped;
// Custom events
void (*event_textChanged)(struct TextBoxUIComponent *, UICanvas *);
DEFINE_UICOMPONENT_END(TextBoxUIComponent);
