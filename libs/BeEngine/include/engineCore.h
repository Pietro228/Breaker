#pragma once

#include <SDL2/SDL.h>
#include <stdlib.h>

#include "gameObject.h"
#include "input.h"
#include "level.h"
#include "renderer.h"
#include "uiCanvas.h"

// Type definitions

typedef struct EngineOptions {
    const char* projectName;
    unsigned int window_x;
    unsigned int window_y;
    unsigned int window_width;
    unsigned int window_height;
    Uint32 window_flags;
    Level initialLevel;
} EngineOptions;

typedef struct EngineEvents {
    void (*event_engineInitialized)();
    void (*event_anyInput)(SDL_Event*);
} EngineEvents;

typedef struct EngineCore {
    EngineOptions options;
    EngineEvents events;
    SDL_Event* lastInputEvent;
    char _executableFolderPath[256];
    Renderer _renderer;
    Level _currentLevel;
    int _loadingLevel;
    InputFocus _inputFocus;
    UICanvas* _focusedUICanvas;
    void* _focusedUIComponent;
} EngineCore;

typedef struct {
    void (*event_tick)(void*);
} EventTick;

// Macros
#ifndef BEENGINE_VERSION_MAJOR

#define BEENGINE_VERSION_MAJOR 1
#define BEENGINE_VERSION_MINOR 0
#define BEENGINE_VERSION_PATCH 0
#define BEENGINE_VERSION_BUILD 1

#endif

#define TRUE 1
#define FALSE 0

#define REG_GAMEOBJECT(gameObject) \
    _engineCore_registerGameObject(gameObject)

#define UNREG_GAMEOBJECT(id) \
    _engineCore_unregisterGameObject(id)

#define NEW_ID rand() % (SIZE_T_MAX + 1)

#define NEW(name) \
    (name*)malloc(sizeof(name))

// Public functions
void engineCore_startGameEngine(EngineOptions* options, EngineEvents* events, int argc, const char* argv[]);
int engineCore_loadLevel(Level* level);
void engineCore_setInputFocus(InputFocus focus);
InputFocus engineCore_getInputFocus();
void engineCore_setFocusedUIComponent(UICanvas* canvas, void* component);
UICanvas* engineCore_getFocusedUICanvas();
void* engineCore_getFocusedUIComponent();

// Getters
EngineCore* getCore();
Level* getLevel();
Renderer* getRenderer();
double getDeltaTime();
char* getExecutableFolderPath();

// Private functions
void _engineCore_initialize(EngineOptions* _options, EngineEvents* _events);
void _engineCore_clean();
void _engineCore_cleanGameObjects();
void _engineCore_cleanUICanvases();

void _engineCore_tick();
void _engineCore_tickGameObjects();
void _engineCore_tickUI();
void _engineCore_anyInput(SDL_Event* event);

GameObject* _engineCore_registerGameObject(GameObject* go);
void _engineCore_unregisterGameObject(GameObject* go);
UICanvas* _engineCore_registerUICanvas();
void _engineCore_unregisterUICanvas(UICanvas* canvas);