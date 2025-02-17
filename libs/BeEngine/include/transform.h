#pragma once

#include "vector2.h"

typedef struct Transform {
    Vector2 position;
    Vector2 size;
} Transform;

#define TRANSFORM(position, size) \
    ((Transform){position, size})

#define TRANSFORM_ZERO \
    ((Transform){VECTOR2_ZERO, VECTOR2_ZERO})
