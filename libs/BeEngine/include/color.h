#pragma once

#include <stdint.h>

#include "SDL.h"

typedef struct Color {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
} Color;

#define COLOR(red, green, blue) \
    ((Color){.r = red, .g = green, .b = blue, .a = 255})

#define COLOR_RGBA(red, green, blue, alpha) \
    ((Color){.r = red, .g = green, .b = blue, .a = alpha})

#define COLOR_RANDOM \
    ((Color){.r = rand() % 256, .g = rand() % 256, .b = rand() % 256, .a = 255})

#define COLOR_RED COLOR(255, 0, 0)
#define COLOR_GREEN COLOR(0, 255, 0)
#define COLOR_BLUE COLOR(0, 0, 255)
#define COLOR_WHITE COLOR(255, 255, 255)
#define COLOR_BLACK COLOR(0, 0, 0)
#define COLOR_YELLOW COLOR(255, 255, 0)
#define COLOR_CYAN COLOR(0, 255, 255)
#define COLOR_MAGENTA COLOR(255, 0, 255)
#define COLOR_ORANGE COLOR(255, 165, 0)
#define COLOR_PURPLE COLOR(128, 0, 128)
#define COLOR_BROWN COLOR(165, 42, 42)
#define COLOR_PINK COLOR(255, 192, 203)
#define COLOR_LIME COLOR(50, 205, 50)
#define COLOR_TEAL COLOR(0, 128, 128)
#define COLOR_GRAY COLOR(128, 128, 128)
#define COLOR_GOLD COLOR(255, 215, 0)
#define COLOR_SILVER COLOR(192, 192, 192)
#define COLOR_NAVY COLOR(0, 0, 128)
#define COLOR_MAROON COLOR(128, 0, 0)
#define COLOR_OLIVE COLOR(128, 128, 0)
#define COLOR_SKYBLUE COLOR(135, 206, 235)

int color_equal(const Color *c1, const Color *c2);
SDL_Color color_toSDL_Color(const Color *color);