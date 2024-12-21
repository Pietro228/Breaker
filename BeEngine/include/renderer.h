#pragma once

#include <SDL2/SDL.h>

#include "color.h"
#include "font.h"
#include "list.h"
#include "vector2.h"

typedef struct Renderer {
    SDL_Window *gameWindow;
    SDL_Renderer *gameRenderer;
    TTF_FontCacheList loadedTtfFonts;
#ifndef NDEBUG
    int debugShowCollisions;
    int debugShowStats;
#endif
} Renderer;

extern int debugShowCollisions, debugShowStats;

int renderer_init();
void renderer_render();

void renderer_drawFillRectangle(const Color *color, const Vector2 *location, const Vector2 *size);
void renderer_drawRectangle(const Color *color, const Vector2 *location, const Vector2 *size);