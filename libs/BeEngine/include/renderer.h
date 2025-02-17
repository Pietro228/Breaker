#pragma once

#include "SDL.h"
#include "cameraGameObjectComp.h"
#include "color.h"
#include "engineApi.h"
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

BEENGINE_API Vector2 renderer_getViewportLocation();
BEENGINE_API Vector2 renderer_getViewportSize();
BEENGINE_API void renderer_rectAdjustByCamera(SDL_Rect *rect);
BEENGINE_API Vector2 renderer_getTextSize(TTF_Font *font, char *text);
BEENGINE_API SDL_Texture *renderer_loadTexture(const char *texturePath);

// Drawing
BEENGINE_API void renderer_UI_drawFillRectangle(Color *color, Vector2 *location, Vector2 *size);
BEENGINE_API void renderer_UI_drawRectangle(Color *color, Vector2 *location, Vector2 *size);
BEENGINE_API void renderer_drawFillRectangle(Color *color, Vector2 *location, Vector2 *size);
BEENGINE_API void renderer_drawRectangle(Color *color, Vector2 *location, Vector2 *size);