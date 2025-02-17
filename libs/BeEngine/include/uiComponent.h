#pragma once

#include "constraint.h"
#include "engineApi.h"
#include "vector2.h"
#include "visibility.h"

#define UICOMPONENT_EVENT_COUNT 10

/*  void*, UICanvas* event_registered
    event_tick
    event_draw
    event_destroyed
    event_clicked
    event_pressed
    event_released
    event_hovered
    event_unhovered
    char displayName[64]
    size_t id
    Vector2 position
    Vector2 size
    Visibility visibility
    int isPressed
    int isHovered
    int disabled
    ConstraintType horizontalConstraint
    ConstraintType verticalConstraint
*/
#define DEFINE_UICOMPONENT_START(name)                         \
    typedef struct name {                                      \
        void (*__event_registered)(struct name *, UICanvas *); \
        void (*__event_tick)(struct name *, UICanvas *);       \
        void (*__event_draw)(struct name *, UICanvas *);       \
        void (*__event_destroyed)(struct name *, UICanvas *);  \
        void (*__event_clicked)(struct name *, UICanvas *);    \
        void (*__event_pressed)(struct name *, UICanvas *);    \
        void (*__event_released)(struct name *, UICanvas *);   \
        void (*__event_hovered)(struct name *, UICanvas *);    \
        void (*__event_unhovered)(struct name *, UICanvas *);  \
        void (*__event_input)(struct name *, UICanvas *);      \
        size_t id;                                             \
        char displayName[64];                                  \
        Vector2 position;                                      \
        Vector2 _actualPosition;                               \
        Thickness margin;                                      \
        Vector2 size;                                          \
        Visibility visibility;                                 \
        int isPressed;                                         \
        int isHovered;                                         \
        int disabled;                                          \
        ConstraintType horizontalConstraint;                   \
        ConstraintType verticalConstraint;                     \
        void (*event_registered)(struct name *, UICanvas *);   \
        void (*event_tick)(struct name *, UICanvas *);         \
        void (*event_draw)(struct name *, UICanvas *);         \
        void (*event_destroyed)(struct name *, UICanvas *);    \
        void (*event_clicked)(struct name *, UICanvas *);      \
        void (*event_pressed)(struct name *, UICanvas *);      \
        void (*event_released)(struct name *, UICanvas *);     \
        void (*event_hovered)(struct name *, UICanvas *);      \
        void (*event_unhovered)(struct name *, UICanvas *);    \
        void (*event_input)(struct name *, UICanvas *);

#define DEFINE_UICOMPONENT_END(name)                                             \
    }                                                                            \
    name;                                                                        \
                                                                                 \
    BEENGINE_API void _##name##_registered(struct name *comp, UICanvas *canvas); \
    BEENGINE_API void _##name##_tick(struct name *comp, UICanvas *canvas);       \
    BEENGINE_API void _##name##_draw(struct name *comp, UICanvas *canvas);       \
    BEENGINE_API void _##name##_destroyed(struct name *comp, UICanvas *canvas);  \
    BEENGINE_API void _##name##_clicked(struct name *comp, UICanvas *canvas);    \
    BEENGINE_API void _##name##_pressed(struct name *comp, UICanvas *canvas);    \
    BEENGINE_API void _##name##_released(struct name *comp, UICanvas *canvas);   \
    BEENGINE_API void _##name##_hovered(struct name *comp, UICanvas *canvas);    \
    BEENGINE_API void _##name##_unhovered(struct name *comp, UICanvas *canvas);  \
    BEENGINE_API void _##name##_input(struct name *comp, UICanvas *canvas);
