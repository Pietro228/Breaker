#pragma once

#include "gameObject.h"
#include "stdlib.h"

#define GAMEOBJECTCOMP_EVENT_COUNT 4

#define DEFINE_GAMEOBJECTCOMP_START(name)                      \
    typedef struct name {                                      \
        void (*event_registered)(struct name *, GameObject *); \
        void (*event_tick)(struct name *, GameObject *);       \
        void (*event_draw)(struct name *, GameObject *);       \
        void (*event_destroyed)(struct name *, GameObject *);  \
        size_t id;                                             \
        Vector2 relativeLocation;                              \
        Vector2 worldLocation;                                 \
        Vector2 size;

#define DEFINE_GAMEOBJECTCOMP_END(name)                               \
    }                                                                 \
    name;                                                             \
                                                                      \
    void _##name##_registered(struct name *comp, GameObject *parent); \
    void _##name##_tick(struct name *comp, GameObject *parent);       \
    void _##name##_draw(struct name *comp, GameObject *parent);       \
    void _##name##_destroyed(struct name *comp, GameObject *parent);