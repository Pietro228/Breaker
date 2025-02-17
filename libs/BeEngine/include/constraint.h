#pragma once

#include "brush.h"
#include "transform.h"

typedef enum ConstraintType {
    CONSTRAINT_RELATIVE = 0,
    CONSTRAINT_CENTERED,
    CONSTRAINT_START,
    CONSTRAINT_END
} ConstraintType;

BEENGINE_API Vector2 constraint_apply(Transform* parentTrans, Transform* childTrans, Thickness* margin, ConstraintType horizontal, ConstraintType vertical);