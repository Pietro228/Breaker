#pragma once

#include "list.h"
#include "uiComponent.h"
#include "visibility.h"

// Type definitions
DEFINE_LIST(UIComponentList, void *);

typedef struct UICanvas {
    size_t id;
    UIComponentList uiComponents;
    Visibility visibility;
    void (*event_register)(struct UICanvas *);
    void (*event_tick)(struct UICanvas *);
    void (*event_destroyed)(struct UICanvas *);
} UICanvas;

DEFINE_LIST(UICanvasList, UICanvas *);

// Macros
#define UICANVAS_ATTACH_COMP(canvas, name, component)        \
    (component)->__event_registered = &_##name##_registered; \
    (component)->__event_tick = &_##name##_tick;             \
    (component)->__event_draw = &_##name##_draw;             \
    (component)->__event_destroyed = &_##name##_destroyed;   \
    (component)->__event_clicked = &_##name##_clicked;       \
    (component)->__event_pressed = &_##name##_pressed;       \
    (component)->__event_released = &_##name##_released;     \
    (component)->__event_hovered = &_##name##_hovered;       \
    (component)->__event_unhovered = &_##name##_unhovered;   \
    (component)->__event_input = &_##name##_input;           \
    _uiCanvas_attachUIComponent(canvas, component);

BEENGINE_API void _uiCanvas_attachUIComponent(UICanvas *canvas, void *uiComponent);