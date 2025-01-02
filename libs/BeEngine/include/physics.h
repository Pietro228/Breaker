#pragma once

typedef enum CollisionType {
    COLLISION_NO_COLLISION = 0,
    COLLISION_BLOCK,
    COLLISION_OVERLAP
} CollisionType;

typedef enum ObjectType {
    OBJECT_STATIC = 0,
    OBJECT_MOVABLE
} ObjectType;