#pragma once

#include <stdio.h>

#include "cameraGameObjectComp.h"
#include "gameObject.h"
#include "uiCanvas.h"
#include "vector2.h"

typedef struct Level {
    size_t id;
    char* name;
    // All objects in the level
    GameObjectList allGameObjects;
    UICanvasList allUICanvases;
    // Functions
    void (*event_loaded)();
} Level;

#define DEFINE_LEVEL(name) \
    extern Level name;     \
    void _##name##_loaded();

#define DECLARE_LEVEL

BEENGINE_API GameObject* level_spawnGameObject(GameObjectConstructor* gameObjectToSpawn, Vector2* location);
BEENGINE_API void level_destroyGameObject(GameObject* gameObject);
BEENGINE_API UICanvas* level_createUICanvas();
BEENGINE_API void level_destroyUICanvas(UICanvas* canvas);
BEENGINE_API void level_focusCamera(CameraGameObjectComp* camera, Vector2* bounds);