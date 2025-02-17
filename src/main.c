#include <conio.h>
#include <stdio.h>

#include "BeEngine.h"
#include "buttonUIComponent.h"
#include "gameLevel.h"
#include "gameObject.h"
#include "level.h"
#include "list.h"
#include "mainMenuLevel.h"
#include "physicsGameObjectComp.h"
#include "testLevel.h"
#include "textureGameObjectComp.h"
#include "uiCanvas.h"
#include "uiComponent.h"

int main(int argc, const char* argv[]) {
    EngineOptions options = {
        .projectName = "Breaker (BeEngineC)",
        .window_x = SDL_WINDOWPOS_CENTERED,
        .window_y = SDL_WINDOWPOS_CENTERED,
        .window_width = 600,   // 800
        .window_height = 800,  // 600
        //.window_flags = SDL_WINDOW_RESIZABLE,
        .initialLevel = MainMenuLevel};

    EngineEvents events = {
        .event_engineInitialized = &event_gameEngineInitialized,
        .event_anyInput = &event_anyInput};

    engineCore_startGameEngine(&options, &events, argc, argv);

    getch();
}

void event_gameEngineInitialized() {
}
