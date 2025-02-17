#pragma once

#include "SDL_ttf.h"
#include "color.h"
#include "list.h"

typedef struct Font {
    char path[256];
    unsigned int size;
    Color color;
    TTF_Font *_ttfFont;
} Font;

DEFINE_LIST(TTF_FontList, TTF_Font *);

typedef struct TTF_FontCache {
    char path[256];
    TTF_FontList fonts;
    IntList sizes;
} TTF_FontCache;

DEFINE_LIST(TTF_FontCacheList, TTF_FontCache);
// TTF_FontCacheList -> TTF_FontCache[] -> TTF_FontList -> TTF_Font[]

BEENGINE_API TTF_Font *font_load(const char *path, const unsigned int size);
void font_cleanup();