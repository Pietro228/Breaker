#pragma once

#include "SDL.h"
#include "brush.h"
#include "color.h"
#include "uiCanvas.h"
#include "uiComponent.h"

// Type definitions
typedef struct ButtonStyle {
    TextureBrush normalBrush;
    TextureBrush hoveredBrush;
    TextureBrush presssedBrush;
    TextureBrush disabledBrush;
} ButtonStyle;

typedef struct ButtonBorderStyle {
    BorderBrush normalBrush;
    BorderBrush hoveredBrush;
    BorderBrush presssedBrush;
    BorderBrush disabledBrush;
} ButtonBorderStyle;

// Macros
#define BUTTONSTYLE(textureBrush_normal, textureBrush_hovered, textureBrush_pressed, textureBrush_disabled) \
    ((ButtonStyle){textureBrush_normal, textureBrush_hovered, textureBrush_pressed, textureBrush_disabled})

#define BUTTONBORDERSTYLE(borderBrush_normal, borderBrush_hovered, borderBrush_pressed, borderBrush_disabled) \
    ((ButtonStyle){borderBrush_normal, borderBrush_hovered, borderBrush_pressed, borderBrush_disabled})

DEFINE_UICOMPONENT_START(ButtonUIComponent);
ButtonStyle style;
ButtonBorderStyle borderStyle;
DEFINE_UICOMPONENT_END(ButtonUIComponent);