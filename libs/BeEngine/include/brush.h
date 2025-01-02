#pragma once

#include "SDL.h"
#include "color.h"

// Type definitions
typedef struct Thickness {
    unsigned int left, top, right, bottom;
} Thickness;

typedef struct TextureBrush {
    Color color;
    char *texturePath;
    SDL_Texture *_SDL_Texture;
} TextureBrush;

typedef struct BorderBrush {
    Color color;
    Thickness thickness;
} BorderBrush;

// Macros
#define TEXTUREBRUSH_DEFAULT \
    ((TextureBrush){COLOR(255, 255, 255), NULL})

#define THICKNESS1(amount) \
    ((Thickness){amount, amount, amount, amount})

#define THICKNESS4(left, top, right, bottom) \
    ((Thickness){left, top, right, bottom})

// Functions
TextureBrush newTextureBrush(Color *color, char *texturePath);

// Idk jestli jen nechat makra hmmm :thinking:
Thickness newThickness1(const unsigned int amount);
Thickness newThickness4(const unsigned int left, const unsigned int top, const unsigned int right, const unsigned int bottom);