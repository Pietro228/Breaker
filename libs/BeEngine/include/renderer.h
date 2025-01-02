#pragma once

#include <SDL2/SDL.h>

#include "cameraGameObjectComp.h"
#include "color.h"
#include "font.h"
#include "list.h"
#include "vector2.h"

typedef struct Renderer {
    SDL_Window *gameWindow;
    SDL_Renderer *gameRenderer;
    TTF_FontCacheList loadedTtfFonts;
    CameraGameObjectComp *focusedCamera;
    TTF_Font *debugFont;
    void (*event_viewportResized)(Vector2 *);
#ifndef NDEBUG
    int debugShowCollisions;
    int debugShowStats;
    SDL_Surface *_statsTextSurface;
    SDL_Texture *_statsTextTexture;
#endif
} Renderer;

int renderer_init();
void renderer_render();

Vector2 renderer_getViewportLocation();
Vector2 renderer_getViewportSize();
void renderer_rectAdjustByCamera(SDL_Rect *rect);
Vector2 renderer_getTextSize(TTF_Font *font, char *text);
SDL_Texture *renderer_loadTexture(const char *texturePath);

void renderer_UI_drawFillRectangle(Color *color, Vector2 *location, Vector2 *size);
void renderer_UI_drawRectangle(Color *color, Vector2 *location, Vector2 *size);
void renderer_drawFillRectangle(Color *color, Vector2 *location, Vector2 *size);
void renderer_drawRectangle(Color *color, Vector2 *location, Vector2 *size);