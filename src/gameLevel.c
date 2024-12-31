#include "gameLevel.h"

#include "color.h"
#include "components.h"
#include "engineCore.h"
#include "level.h"
#include "logger.h"
#include "mainMenuLevel.h"

#define AMOUNT_OF_BLOCKS 10
#define BLOCK_SIZE_X 30
#define BLOCK_SIZE_X_OFFSET (BLOCK_SIZE_X + BLOCK_SIZE_X / 2)
#define BLOCK_SIZE_Y 10
#define BLOCK_SIZE_Y_OFFSET (BLOCK_SIZE_Y * 3)
#define WALL_WIDTH 10
#define BALL_SIZE 10
#define BALL_VELOCITY 300

Level GameLevel = {.id = 100, .name = "GameLevel", .event_loaded = &_GameLevel_loaded};

GameObjectList blocks;
GameObject *cameraGObject, *leftWallGObject, *rightWallGObject, *topWallGObject, *bottomVoidGObject, *ballGObject, *ballCollisionGObject, *paddleGObject;

void _GameLevel_loaded() {
    // Assign events
    getRenderer()->event_viewportResized = &windowResized;

    // Camera
    GameObjectConstructor cameraGObjectConstructor = {};

    Vector2 viewport = renderer_getViewportSize();
    cameraGObject = level_spawnGameObject(&cameraGObjectConstructor, &VECTOR2(viewport.x / 2, viewport.y / 2));
    CameraGameObjectComp* cameraComp = NEW_GAMEOBJECTCOMP(CameraGameObjectComp);
    GAMEOBJECT_ATTACH_COMP(cameraGObject, CameraGameObjectComp, cameraComp);

    level_focusCamera(cameraComp, &VECTOR2(-1, viewport.y));

    // Blocks
    GameObjectConstructor blockGObjectConstructor = {.collisionType = COLLISION_BLOCK, .size = VECTOR2(BLOCK_SIZE_X, BLOCK_SIZE_Y)};

    for (int i = 0; i < AMOUNT_OF_BLOCKS; i++) {
        for (int j = 0; j < 5; j++) {
            GameObject* blockGObject = level_spawnGameObject(&blockGObjectConstructor, &VECTOR2((viewport.x / 2 - BLOCK_SIZE_X_OFFSET * (AMOUNT_OF_BLOCKS / 2)) + i * BLOCK_SIZE_X_OFFSET + BLOCK_SIZE_X / 4, 50 + j * BLOCK_SIZE_Y_OFFSET));

            CubeGameObjectComp* cubeComp = NEW_GAMEOBJECTCOMP(CubeGameObjectComp);
            (*cubeComp) = (CubeGameObjectComp){.color = COLOR_PURPLE, .size = VECTOR2(BLOCK_SIZE_X, BLOCK_SIZE_Y)};
            GAMEOBJECT_ATTACH_COMP(blockGObject, CubeGameObjectComp, cubeComp);

            LIST_ADD(blocks, GameObject*, blockGObject);
        }
    }

    // Walls
    GameObjectConstructor wallGObjectConstructor = {.collisionType = COLLISION_BLOCK, .size = VECTOR2(WALL_WIDTH, viewport.y)};
    CubeGameObjectComp wallComp = {.color = COLOR_WHITE, .size = VECTOR2(WALL_WIDTH, viewport.y)};

    // Left wall
    leftWallGObject = level_spawnGameObject(&wallGObjectConstructor, &VECTOR2(0, 0));

    CubeGameObjectComp* leftWallComp = NEW_GAMEOBJECTCOMP(CubeGameObjectComp);
    (*leftWallComp) = wallComp;

    GAMEOBJECT_ATTACH_COMP(leftWallGObject, CubeGameObjectComp, leftWallComp);

    // Right wall
    rightWallGObject = level_spawnGameObject(&wallGObjectConstructor, &VECTOR2(viewport.x - WALL_WIDTH, 0));

    CubeGameObjectComp* rightWallComp = NEW_GAMEOBJECTCOMP(CubeGameObjectComp);
    (*rightWallComp) = wallComp;

    GAMEOBJECT_ATTACH_COMP(rightWallGObject, CubeGameObjectComp, rightWallComp);

    // Top wall
    GameObjectConstructor topWallGObjectConstructor = {.collisionType = COLLISION_BLOCK, .size = VECTOR2(viewport.x, WALL_WIDTH)};

    topWallGObject = level_spawnGameObject(&topWallGObjectConstructor, &VECTOR2(0, 0));

    CubeGameObjectComp* topWallComp = NEW_GAMEOBJECTCOMP(CubeGameObjectComp);
    (*topWallComp) = (CubeGameObjectComp){.color = COLOR_WHITE, .size = VECTOR2(viewport.x, WALL_WIDTH)};

    GAMEOBJECT_ATTACH_COMP(topWallGObject, CubeGameObjectComp, topWallComp);

    // Bottom void
    GameObjectConstructor bottomVoidGObjectConstructor = {.collisionType = COLLISION_OVERLAP, .size = VECTOR2(viewport.x, WALL_WIDTH)};

    bottomVoidGObject = level_spawnGameObject(&bottomVoidGObjectConstructor, &VECTOR2(0, viewport.y - WALL_WIDTH));

    // Ball
    GameObjectConstructor ballGObjectConstructor = {
        .collisionType = COLLISION_OVERLAP,
        .size = VECTOR2(BALL_SIZE, BALL_SIZE),
        .objectType = OBJECT_MOVABLE,
        .event_beginOverlap = &event_ballCollision_beginOverlap};

    ballGObject = level_spawnGameObject(&ballGObjectConstructor, &VECTOR2(viewport.x / 2, viewport.y - 50));

    CubeGameObjectComp* ballComp = NEW_GAMEOBJECTCOMP(CubeGameObjectComp);
    (*ballComp) = (CubeGameObjectComp){.color = COLOR_NAVY, .size = VECTOR2(BALL_SIZE, BALL_SIZE)};
    GAMEOBJECT_ATTACH_COMP(ballGObject, CubeGameObjectComp, ballComp);

    PhysicsGameObjectComp* ballPhysicsComp = NEW_GAMEOBJECTCOMP(PhysicsGameObjectComp);
    GAMEOBJECT_ATTACH_COMP(ballGObject, PhysicsGameObjectComp, ballPhysicsComp);

    gameObject_setVelocity(ballGObject, &VECTOR2(BALL_VELOCITY, BALL_VELOCITY));

    // Paddle
    GameObjectConstructor paddleGObjectConstructor = {.collisionType = COLLISION_BLOCK, .size = VECTOR2(100, 10), .objectType = OBJECT_MOVABLE};

    paddleGObject = level_spawnGameObject(&paddleGObjectConstructor, &VECTOR2(viewport.x / 2 - 50, viewport.y - 20));

    CubeGameObjectComp* paddleComp = NEW_GAMEOBJECTCOMP(CubeGameObjectComp);
    (*paddleComp) = (CubeGameObjectComp){.color = COLOR_GREEN, .size = VECTOR2(100, 10)};
    GAMEOBJECT_ATTACH_COMP(paddleGObject, CubeGameObjectComp, paddleComp);

    PhysicsGameObjectComp* paddlePhysicsComp = NEW_GAMEOBJECTCOMP(PhysicsGameObjectComp);
    GAMEOBJECT_ATTACH_COMP(paddleGObject, PhysicsGameObjectComp, paddlePhysicsComp);
}

void windowResized(Vector2* newSize) {
    cameraGObject->location.y = newSize->y / 2;
}

void event_ballCollision_beginOverlap(GameObject* self, GameObject* collidedWith) {
    LOG("Ball hit something");

    int blockIndex = LIST_FIND_INDEX(blocks, GameObject*, , collidedWith);
    if (blockIndex != -1) {
        LOG("Ball hit block");
        // LIST_REMOVE(blocks, GameObject*, blockIndex);
        // level_destroyGameObject(collidedWith);
        collidedWith->location = VECTOR2(-100, 0);

        // Použiju SDL_HasIntersection a udělám to jako line trace nahoru, dolů, doleva, doprava a tak zjistím kde hitnul
        if (self->location.y < collidedWith->location.y + collidedWith->size.y || self->location.y + self->size.y > collidedWith->location.y) {
            LOG("Ball hit block y");
            gameObject_setVelocity(ballGObject, &VECTOR2(ballGObject->velocity.x, -ballGObject->velocity.y));
        }

        return;
    }

    if (collidedWith == bottomVoidGObject) {
        LOG("Ball hit bottom void");
        // engineCore_loadLevel(&MainMenuLevel);
        return;
    }

    if (collidedWith == leftWallGObject || collidedWith == rightWallGObject) {
        LOG("Ball hit lefr or right wall");
        gameObject_setVelocity(ballGObject, &VECTOR2(-ballGObject->velocity.x, ballGObject->velocity.y));
        // LOG("Unregister result: %d", level_destroyGameObject(collidedWith));
        return;
    }

    if (collidedWith == topWallGObject) {
        LOG("Ball hit top wall");
        gameObject_setVelocity(ballGObject, &VECTOR2(ballGObject->velocity.x, -ballGObject->velocity.y));
        return;
    }

    if (collidedWith == paddleGObject) {
        LOG("Ball hit paddle");
        gameObject_setVelocity(ballGObject, &VECTOR2(ballGObject->velocity.x, -ballGObject->velocity.y));
        return;
    }
}

void event_anyInput(SDL_Event* event) {
    SDL_Keycode code = event->key.keysym.sym;

    float vel = 400;

    if (event->type == SDL_KEYDOWN) {
        if (code == SDLK_a)
            paddleGObject->velocity.x = -vel;
        else if (code == SDLK_d)
            paddleGObject->velocity.x = vel;
    } else if (event->type == SDL_KEYUP) {
        if (code == SDLK_a && paddleGObject->velocity.x == -vel)
            paddleGObject->velocity.x = 0;
        else if (code == SDLK_d && paddleGObject->velocity.x == vel)
            paddleGObject->velocity.x = 0;
    }
}