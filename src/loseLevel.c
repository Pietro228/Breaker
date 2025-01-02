#include "loseLevel.h"

#include "BeEngineUI.h"
#include "engineCore.h"
#include "mainMenuLevel.h"

Level LoseLevel = {.id = 102, .name = "LoseLevel", .event_loaded = &_LoseLevel_loaded};

void _LoseLevel_loaded() {
    UICanvas* loseCanvas = level_createUICanvas();

    // "Game over!" text
    TextUIComponent* loseText = NEW(TextUIComponent);
    (*loseText) = (TextUIComponent){.id = 1, .position = VECTOR2(100, 50), .text = "Game over!", .font = (Font){.size = 50, .path = "assets/fonts/AvrileSansUI-Regular.ttf", .color = COLOR_WHITE}};
    UICANVAS_ATTACH_COMP(loseCanvas, TextUIComponent, loseText);

    // Main menu button
    ButtonUIComponent* mainMenuButton = NEW(ButtonUIComponent);
    (*mainMenuButton) = (ButtonUIComponent){.id = 2,
                                            .position = VECTOR2(0, 150),
                                            .horizontalConstraint = CONSTRAINT_CENTERED,
                                            .size = VECTOR2(200, 35),
                                            .style = BUTTONSTYLE(newTextureBrush(&COLOR(255, 255, 255), NULL),
                                                                 newTextureBrush(&COLOR(230, 230, 230), NULL),
                                                                 newTextureBrush(&COLOR(200, 200, 200), NULL),
                                                                 TEXTUREBRUSH_DEFAULT),
                                            .event_clicked = &event_mainMenuButton_clicked};
    UICANVAS_ATTACH_COMP(loseCanvas, ButtonUIComponent, mainMenuButton);

    TextUIComponent* mainMenuButtonText = NEW(TextUIComponent);
    (*mainMenuButtonText) = (TextUIComponent){.id = 3, .position = VECTOR2(225, 150), .text = "MAIN MENU", .font = (Font){.size = 25, .path = "assets/fonts/AvrileSansUI-Regular.ttf", .color = COLOR_BLACK}};
    UICANVAS_ATTACH_COMP(loseCanvas, TextUIComponent, mainMenuButtonText);
}

void event_mainMenuButton_clicked(ButtonUIComponent* button, UICanvas* canvas) {
    engineCore_loadLevel(&MainMenuLevel);
}
