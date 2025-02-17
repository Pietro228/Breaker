#include "levelSelectionLevel.h"

#include "BeEngineUI.h"
#include "engineCore.h"
#include "gameLevel.h"
#include "logger.h"

Level LevelSelectionLevel = {.id = 103, .name = "LevelSelectionLevel", .event_loaded = &_LevelSelectionLevel_loaded};

TextBoxUIComponent *ballVelocityTextbox;

void _LevelSelectionLevel_loaded() {
    UICanvas *lsCanvas = level_createUICanvas();

    // "Select a level" text
    TextUIComponent *selectText = NEW(TextUIComponent);
    (*selectText) = (TextUIComponent){.id = 1, .position = VECTOR2(100, 50), .text = "Select a level", .font = (Font){.size = 50, .path = "assets/fonts/AvrileSansUI-Regular.ttf", .color = COLOR_WHITE}};
    UICANVAS_ATTACH_COMP(lsCanvas, TextUIComponent, selectText);

    // Ball velocity label
    TextUIComponent *ballVelocityLabel = NEW(TextUIComponent);
    (*ballVelocityLabel) = (TextUIComponent){.id = 2, .position = VECTOR2(100, 120), .text = "Ball velocity", .font = (Font){.size = 25, .path = "assets/fonts/AvrileSansUI-Regular.ttf", .color = COLOR_WHITE}};
    UICANVAS_ATTACH_COMP(lsCanvas, TextUIComponent, ballVelocityLabel);

    // Ball velocity textBox
    ballVelocityTextbox = NEW(TextBoxUIComponent);
    (*ballVelocityTextbox) = (TextBoxUIComponent){.id = 3,
                                                  .position = VECTOR2(100, 160),
                                                  .size = VECTOR2(400, 45),
                                                  .text = "400",
                                                  .backgroundBrush = newTextureBrush(&COLOR(50, 50, 50), NULL),
                                                  .borderBrush = (BorderBrush){.color = COLOR(100, 100, 100), .thickness = THICKNESS1(1)},
                                                  .focusedBorderBrush = (BorderBrush){.color = COLOR_GREEN, .thickness = THICKNESS1(2)},
                                                  .font = (Font){.size = 25, .path = "assets/fonts/AvrileSansUI-Regular.ttf", .color = COLOR_WHITE},
                                                  .padding = THICKNESS4(5, 5, 0, 0)};
    UICANVAS_ATTACH_COMP(lsCanvas, TextBoxUIComponent, ballVelocityTextbox);

    // "Level 1" button
    ButtonUIComponent *level1Button = NEW(ButtonUIComponent);
    (*level1Button) = (ButtonUIComponent){.id = 4,
                                          .position = VECTOR2(100, 220),
                                          .size = VECTOR2(200, 35),
                                          .style = BUTTONSTYLE(newTextureBrush(&COLOR(255, 255, 255), NULL),
                                                               newTextureBrush(&COLOR(230, 230, 230), NULL),
                                                               newTextureBrush(&COLOR(200, 200, 200), NULL),
                                                               TEXTUREBRUSH_DEFAULT),
                                          .event_clicked = &event_level1Button_clicked};
    UICANVAS_ATTACH_COMP(lsCanvas, ButtonUIComponent, level1Button);

    // "Level 1" text
    TextUIComponent *level1Text = NEW(TextUIComponent);
    (*level1Text) = (TextUIComponent){.id = 5, .position = VECTOR2(110, 220), .text = "Level 1", .font = (Font){.size = 25, .path = "assets/fonts/AvrileSansUI-Regular.ttf", .color = COLOR_BLACK}};
    UICANVAS_ATTACH_COMP(lsCanvas, TextUIComponent, level1Text);

    // "Level 2" button
    ButtonUIComponent *level2Button = NEW(ButtonUIComponent);
    (*level2Button) = (ButtonUIComponent){.id = 6,
                                          .position = VECTOR2(100, 260),
                                          .size = VECTOR2(200, 35),
                                          .style = BUTTONSTYLE(newTextureBrush(&COLOR(255, 255, 255), NULL),
                                                               newTextureBrush(&COLOR(230, 230, 230), NULL),
                                                               newTextureBrush(&COLOR(200, 200, 200), NULL),
                                                               TEXTUREBRUSH_DEFAULT),
                                          .event_clicked = &event_level2Button_clicked};
    UICANVAS_ATTACH_COMP(lsCanvas, ButtonUIComponent, level2Button);

    // "Level 2" text
    TextUIComponent *level2Text = NEW(TextUIComponent);
    (*level2Text) = (TextUIComponent){.id = 7, .position = VECTOR2(110, 260), .text = "Level 2", .font = (Font){.size = 25, .path = "assets/fonts/AvrileSansUI-Regular.ttf", .color = COLOR_BLACK}};
    UICANVAS_ATTACH_COMP(lsCanvas, TextUIComponent, level2Text);
}

void event_level1Button_clicked(ButtonUIComponent *comp, UICanvas *canvas) {
    gameState.ballSpeed = atoi(ballVelocityTextbox->text);
    gameState.level = 1;
    engineCore_loadLevel(&GameLevel);
}

void event_level2Button_clicked(ButtonUIComponent *comp, UICanvas *canvas) {
    gameState.ballSpeed = atoi(ballVelocityTextbox->text);
    gameState.level = 2;
    engineCore_loadLevel(&GameLevel);
}