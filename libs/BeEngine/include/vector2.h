#pragma once

#include "SDL.h"
#include "engineApi.h"

typedef struct Vector2 {
    float x;
    float y;
} Vector2;

#define VECTOR2(x, y) \
    ((Vector2){x, y})

#define VECTOR2_1(x) \
    ((Vector2){x, x})

#define VECTOR2_ZERO \
    ((Vector2){.x = 0, .y = 0})

BEENGINE_API SDL_Rect vector2x2toSDL_Rect(Vector2 *v1, Vector2 *v2);
BEENGINE_API Vector2 vector2_add(Vector2 *v1, Vector2 *v2);
BEENGINE_API Vector2 vector2_sub(Vector2 *v1, Vector2 *v2);
BEENGINE_API Vector2 vector2_mul(Vector2 *v1, float val);
BEENGINE_API Vector2 vector2_div(Vector2 *v1, float val);