#include "mainMenuLevel.h"

#include "buttonUIComponent.h"
#include "engineCore.h"
#include "idkLevel.h"
#include "input.h"
#include "testLevel.h"

Level mainMenuLevel = {.id = 2, .name = "mainMenuLevel", .event_loaded = &_mainMenuLevel_loaded};

ButtonUIComponent playButton;
UICanvas *canvas;

void _mainMenuLevel_loaded() {
    ButtonStyle style = BUTTONSTYLE(newTextureBrush(&COLOR(255, 0, 0), NULL),
                                    newTextureBrush(&COLOR(0, 255, 0), NULL),
                                    newTextureBrush(&COLOR(0, 0, 255), NULL),
                                    TEXTUREBRUSH_DEFAULT);

    canvas = level_createUICanvas();

    playButton = (ButtonUIComponent){.id = 10, .position = VECTOR2(100, 100), .size = VECTOR2(200, 50), .style = style, .event_clicked = &_playButton_clicked};
    playButton.horizontalConstraint = CONSTRAINT_CENTERED;

    UICANVAS_ATTACH_COMP(ButtonUIComponent, &playButton, canvas);
}

void _playButton_clicked(ButtonUIComponent *comp, UICanvas *canvas) {
    engineCore_loadLevel(&testLevel);
}