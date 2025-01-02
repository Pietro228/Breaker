#include "winLevel.h"

#include "BeEngineUI.h"
#include "brush.h"
#include "engineCore.h"
#include "gameLevel.h"
#include "leaderboard.h"
#include "logger.h"
#include "mainMenuLevel.h"
#include "stdio.h"

Level WinLevel = {.id = 101, .name = "WinLevel", .event_loaded = &_WinLevel_loaded};

TextBoxUIComponent* nameTextbox;
UICanvas* winCanvas;

void _WinLevel_loaded() {
    initializeWinLevelUI();
}

void initializeWinLevelUI() {
    LOG("Initializing Win UI...");

    winCanvas = level_createUICanvas();

    // "You win!" text
    TextUIComponent* winText = NEW(TextUIComponent);
    (*winText) = (TextUIComponent){.id = 1, .position = VECTOR2(100, 50), .text = "You win!", .font = (Font){.size = 50, .path = "assets/fonts/AvrileSansUI-Regular.ttf", .color = COLOR_WHITE}};
    UICANVAS_ATTACH_COMP(winCanvas, TextUIComponent, winText);

    // "Your name" label
    TextUIComponent* nameLabel = NEW(TextUIComponent);
    (*nameLabel) = (TextUIComponent){.id = 2, .position = VECTOR2(100, 130), .text = "Your name", .font = (Font){.size = 25, .path = "assets/fonts/AvrileSansUI-Regular.ttf", .color = COLOR_WHITE}};
    UICANVAS_ATTACH_COMP(winCanvas, TextUIComponent, nameLabel);

    // Textbox for name input
    nameTextbox = NEW(TextBoxUIComponent);
    (*nameTextbox) = (TextBoxUIComponent){.id = 3,
                                          .position = VECTOR2(100, 170),
                                          .size = VECTOR2(400, 45),
                                          .backgroundBrush = newTextureBrush(&COLOR(50, 50, 50), NULL),
                                          .borderBrush = (BorderBrush){.color = COLOR(100, 100, 100), .thickness = THICKNESS1(1)},
                                          .focusedBorderBrush = (BorderBrush){.color = COLOR_GREEN, .thickness = THICKNESS1(2)},
                                          .font = (Font){.size = 20, .path = "assets/fonts/AvrileSansUI-Regular.ttf", .color = COLOR_WHITE},
                                          .padding = THICKNESS4(5, 8, 0, 0)};
    UICANVAS_ATTACH_COMP(winCanvas, TextBoxUIComponent, nameTextbox);

    // Submit button
    ButtonUIComponent* submitButton = NEW(ButtonUIComponent);
    (*submitButton) = (ButtonUIComponent){.id = 4,
                                          .position = VECTOR2(100, 225),
                                          .size = VECTOR2(200, 35),
                                          .style = BUTTONSTYLE(newTextureBrush(&COLOR(255, 255, 255), NULL),
                                                               newTextureBrush(&COLOR(230, 230, 230), NULL),
                                                               newTextureBrush(&COLOR(200, 200, 200), NULL),
                                                               TEXTUREBRUSH_DEFAULT),
                                          .event_clicked = &submitButtonClicked};
    UICANVAS_ATTACH_COMP(winCanvas, ButtonUIComponent, submitButton);

    // Submit text
    TextUIComponent* submitText = NEW(TextUIComponent);
    (*submitText) = (TextUIComponent){.id = 5, .position = VECTOR2(110, 225), .text = "SUBMIT", .font = (Font){.size = 25, .path = "assets/fonts/AvrileSansUI-Regular.ttf", .color = COLOR_BLACK}};
    UICANVAS_ATTACH_COMP(winCanvas, TextUIComponent, submitText);
}

void submitButtonClicked(ButtonUIComponent* button, UICanvas* canvas) {
    char leaderboardPath[256];
    strcpy(leaderboardPath, getExecutableFolderPath());
    strcat(leaderboardPath, "/leaderboard.txt");
    FILE* f = fopen(leaderboardPath, "a");

    LeaderboardEntry entry = {.score = gameState.score};
    strlcpy(entry.name, nameTextbox->text, 50);

    fprintf(f, "%s|%d\n", entry.name, entry.score);

    fclose(f);

    engineCore_loadLevel(&MainMenuLevel);
}