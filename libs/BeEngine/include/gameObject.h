#pragma once

#include "limits.h"
#include "list.h"
#include "physics.h"
#include "stdlib.h"
#include "vector2.h"

DEFINE_LIST(GameObjectList, struct GameObject*);
DEFINE_LIST(GameObjectCompList, void*);

typedef struct GameObjectConstructor {
    Vector2 size;
    CollisionType collisionType;
    ObjectType objectType;
    void* properties;
    void (*event_draw)(struct GameObject*);
    void (*event_tick)(struct GameObject*);
    void (*event_destroyed)(struct GameObject*);
    void (*event_beginOverlap)(struct GameObject*, struct GameObject*);   // Self, Collided object
    void (*event_endOverlap)(struct GameObject*, struct GameObject*);     // Self, Collided object
    void (*event_hit)(struct GameObject*, struct GameObject*, Vector2*);  // Self, Collided object, Hit normal
} GameObjectConstructor;

typedef struct GameObject {
    size_t id;
    Vector2 location;
    Vector2 size;
    Vector2 velocity;
    CollisionType collisionType;
    ObjectType objectType;
    struct GameObject* parentGameObject;
    Vector2 relativeLocation;
    GameObjectList overlappedGameObjects;
    GameObjectCompList components;
    void* properties;
    void (*event_draw)(struct GameObject*);
    void (*event_tick)(struct GameObject*);
    void (*event_destroyed)(struct GameObject*);
    void (*event_beginOverlap)(struct GameObject*, struct GameObject*);   // Self, Collided object
    void (*event_endOverlap)(struct GameObject*, struct GameObject*);     // Self, Collided object
    void (*event_hit)(struct GameObject*, struct GameObject*, Vector2*);  // Self, Collided object, Hit normal
} GameObject;

#define GAMEOBJECT_ATTACH_COMP(gameObject, type, component) \
    (component)->event_registered = &_##type##_registered;  \
    (component)->event_tick = &_##type##_tick;              \
    (component)->event_draw = &_##type##_draw;              \
    (component)->event_destroyed = &_##type##_destroyed;    \
    _gameObject_attachComponent(gameObject, component);

// Private
/**
 * DO NOT USE! Use "GAMEOBJECT_ATTACH_COMP" instead.
 *
 * \param go Game object.
 * \param component Game object component.
 */
int _gameObject_attachComponent(GameObject* go, void* component);

// Public
void gameObject_attachToGameObject(GameObject* go, GameObject* goParent);
void gameObject_setVelocity(GameObject* go, Vector2* velocity);
void gameObject_addVelocity(GameObject* go, Vector2* velocity);