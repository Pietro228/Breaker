#include "mainMenuLevel.h"

#include "BeEngineUI.h"
#include "SDL_ttf.h"
#include "engineCore.h"
#include "gameLevel.h"
#include "gameLoop.h"
#include "idkLevel.h"
#include "input.h"
#include "leaderboard.h"
#include "levelSelectionLevel.h"
#include "logger.h"

Level MainMenuLevel = {.id = 2, .name = "mainMenuLevel", .event_loaded = &_MainMenuLevel_loaded};

UICanvas *mainMenuCanvas;

void _MainMenuLevel_loaded() {
    ButtonStyle style = BUTTONSTYLE(newTextureBrush(&COLOR(255, 255, 255), NULL),
                                    newTextureBrush(&COLOR(230, 230, 230), NULL),
                                    newTextureBrush(&COLOR(200, 200, 200), NULL),
                                    TEXTUREBRUSH_DEFAULT);

    mainMenuCanvas = level_createUICanvas();

    ButtonUIComponent *playButton = NEW(ButtonUIComponent);
    (*playButton) = (ButtonUIComponent){.id = 10, .position = VECTOR2(50, 100), .size = VECTOR2(200, 35), .style = style, .event_clicked = &event_playButton_clicked};
    UICANVAS_ATTACH_COMP(mainMenuCanvas, ButtonUIComponent, playButton);

    TextUIComponent *playButtonText = NEW(TextUIComponent);
    (*playButtonText) = (TextUIComponent){.id = 11, .position = VECTOR2(60, 100), .text = "PLAY", .font = (Font){.size = 25, .path = "assets/fonts/AvrileSansUI-Regular.ttf", .color = COLOR_BLACK}};
    UICANVAS_ATTACH_COMP(mainMenuCanvas, TextUIComponent, playButtonText);

    TextUIComponent *titleText = NEW(TextUIComponent);
    (*titleText) = (TextUIComponent){
        .id = 12,
        .position = VECTOR2(0, 20),
        .text = "Breaker",
        .font = (Font){.size = 50, .path = "assets/fonts/AvrileSansUI-Regular.ttf", .color = COLOR_WHITE},
        .horizontalConstraint = CONSTRAINT_CENTERED};
    UICANVAS_ATTACH_COMP(mainMenuCanvas, TextUIComponent, titleText);
    titleText->size = renderer_getTextSize(titleText->font._ttfFont, titleText->text);

    ButtonUIComponent *quitButton = NEW(ButtonUIComponent);
    (*quitButton) = (ButtonUIComponent){.id = 13, .position = VECTOR2(50, 150), .size = VECTOR2(200, 35), .style = style, .event_clicked = &event_quitButton_clicked};
    UICANVAS_ATTACH_COMP(mainMenuCanvas, ButtonUIComponent, quitButton);

    TextUIComponent *quitText = NEW(TextUIComponent);
    (*quitText) = (TextUIComponent){.id = 14, .position = VECTOR2(60, 150), .text = "QUIT", .font = (Font){.size = 25, .path = "assets/fonts/AvrileSansUI-Regular.ttf", .color = COLOR_BLACK}};
    UICANVAS_ATTACH_COMP(mainMenuCanvas, TextUIComponent, quitText);

    showLeaderboard();
}

void showLeaderboard() {
    TextUIComponent *leaderboardText = NEW(TextUIComponent);
    (*leaderboardText) = (TextUIComponent){.id = 16, .position = VECTOR2(50, 250), .text = "Leaderboard", .font = (Font){.size = 30, .path = "assets/fonts/AvrileSansUI-Regular.ttf", .color = COLOR_WHITE}};
    UICANVAS_ATTACH_COMP(mainMenuCanvas, TextUIComponent, leaderboardText);

    // Show leaderboard
    char leaderboardPath[256];
    strcpy(leaderboardPath, getExecutableFolderPath());
    strcat(leaderboardPath, "/leaderboard.txt");
    FILE *f = fopen(leaderboardPath, "rb");

    if (f == NULL) {
        LOG("Leaderboard file not found");
        return;
    }

    // Get lines from file
    char line[100];
    int entryIndex = 0;

    while (fgets(line, sizeof(line), f) && entryIndex < 10) {
        LeaderboardEntry entry;

        strcpy(entry.name, strtok(line, "|"));
        entry.score = atoi(strtok(NULL, "|"));

        TextUIComponent *entryText = NEW(TextUIComponent);
        (*entryText) = (TextUIComponent){.id = 15, .position = VECTOR2(50, 300 + entryIndex * 30), .font = (Font){.size = 20, .path = "assets/fonts/AvrileSansUI-Regular.ttf", .color = COLOR_WHITE}};
        snprintf(entryText->text, 256, "%s - %d", entry.name, entry.score);

        UICANVAS_ATTACH_COMP(mainMenuCanvas, TextUIComponent, entryText);

        LOG("Entry: %s", entryText->text);

        entryIndex++;
    }

    fclose(f);
}

void event_playButton_clicked(ButtonUIComponent *comp, UICanvas *canvas) {
    engineCore_loadLevel(&LevelSelectionLevel);
}

void event_quitButton_clicked(ButtonUIComponent *comp, UICanvas *canvas) {
    exitRequested = TRUE;
}