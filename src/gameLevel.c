#include "gameLevel.h"

#include "BeEngineUI.h"
#include "color.h"
#include "components.h"
#include "engineCore.h"
#include "level.h"
#include "logger.h"
#include "loseLevel.h"
#include "mainMenuLevel.h"
#include "sound.h"
#include "winLevel.h"

#define AMOUNT_OF_BLOCKS_X 10
#define AMOUNT_OF_BLOCKS_Y 1
#define BLOCK_SIZE_X 30
#define BLOCK_SIZE_Y 15
#define WALL_WIDTH 10
#define BALL_SIZE 10
#define BALL_VELOCITY 800
#define TOP_WALL_OFFSET 100

Level GameLevel = {.id = 100, .name = "GameLevel", .event_loaded = &_GameLevel_loaded};
GameState gameState;

AllBlocks blocks;
GameObject
    *backgroundGObject,
    *cameraGObject,
    *leftWallGObject,
    *rightWallGObject,
    *topWallGObject,
    *bottomVoidGObject,
    *ballGObject,
    *paddleGObject;
TextUIComponent *scoreText, *livesText;

void _GameLevel_loaded() {
    // Assign events
    getRenderer()->event_viewportResized = &windowResized;

    // Initialize game state
    gameState = (GameState){.score = 0, .lives = 3, .playing = 0, .ballSpeed = gameState.ballSpeed, .level = gameState.level};

    // Camera
    GameObjectConstructor cameraGObjectConstructor = {};

    Vector2 viewport = renderer_getViewportSize();
    cameraGObject = level_spawnGameObject(&cameraGObjectConstructor, &VECTOR2(viewport.x / 2, viewport.y / 2));
    CameraGameObjectComp* cameraComp = NEW(CameraGameObjectComp);
    GAMEOBJECT_ATTACH_COMP(cameraGObject, CameraGameObjectComp, cameraComp);

    level_focusCamera(cameraComp, &VECTOR2(-1, viewport.y));

    // Background
    GameObjectConstructor backgroundGObjectConstructor = {.size = VECTOR2(viewport.x, viewport.y), .collisionType = COLLISION_NO_COLLISION, .objectType = OBJECT_STATIC};

    backgroundGObject = level_spawnGameObject(&backgroundGObjectConstructor, &VECTOR2(0, 0));

    CubeGameObjectComp* backgroundComp = NEW(CubeGameObjectComp);
    (*backgroundComp) = (CubeGameObjectComp){.color = COLOR(50, 50, 50), .size = VECTOR2(viewport.x, viewport.y)};
    GAMEOBJECT_ATTACH_COMP(backgroundGObject, CubeGameObjectComp, backgroundComp);

    // Walls
    GameObjectConstructor wallGObjectConstructor = {.collisionType = COLLISION_BLOCK, .size = VECTOR2(WALL_WIDTH, viewport.y - TOP_WALL_OFFSET)};
    CubeGameObjectComp wallComp = {.color = COLOR_WHITE, .size = VECTOR2(WALL_WIDTH, viewport.y - TOP_WALL_OFFSET)};

    // Left wall
    leftWallGObject = level_spawnGameObject(&wallGObjectConstructor, &VECTOR2(0, TOP_WALL_OFFSET));

    CubeGameObjectComp* leftWallComp = NEW(CubeGameObjectComp);
    (*leftWallComp) = wallComp;

    GAMEOBJECT_ATTACH_COMP(leftWallGObject, CubeGameObjectComp, leftWallComp);

    // Right wall
    rightWallGObject = level_spawnGameObject(&wallGObjectConstructor, &VECTOR2(viewport.x - WALL_WIDTH, TOP_WALL_OFFSET));

    CubeGameObjectComp* rightWallComp = NEW(CubeGameObjectComp);
    (*rightWallComp) = wallComp;

    GAMEOBJECT_ATTACH_COMP(rightWallGObject, CubeGameObjectComp, rightWallComp);

    // Top wall
    GameObjectConstructor topWallGObjectConstructor = {.collisionType = COLLISION_BLOCK, .size = VECTOR2(viewport.x, WALL_WIDTH)};

    topWallGObject = level_spawnGameObject(&topWallGObjectConstructor, &VECTOR2(0, TOP_WALL_OFFSET));

    CubeGameObjectComp* topWallComp = NEW(CubeGameObjectComp);
    (*topWallComp) = (CubeGameObjectComp){.color = COLOR_WHITE, .size = VECTOR2(viewport.x, WALL_WIDTH)};

    GAMEOBJECT_ATTACH_COMP(topWallGObject, CubeGameObjectComp, topWallComp);

    // Bottom void
    GameObjectConstructor bottomVoidGObjectConstructor = {.collisionType = COLLISION_OVERLAP, .size = VECTOR2(viewport.x, WALL_WIDTH)};

    bottomVoidGObject = level_spawnGameObject(&bottomVoidGObjectConstructor, &VECTOR2(0, viewport.y - WALL_WIDTH));

    // Ball
    GameObjectConstructor ballGObjectConstructor = {
        .collisionType = COLLISION_BLOCK,
        .size = VECTOR2(BALL_SIZE, BALL_SIZE),
        .objectType = OBJECT_MOVABLE,
        .event_hit = &event_ball_hit,
        .event_beginOverlap = &event_ball_beginOverlap};

    ballGObject = level_spawnGameObject(&ballGObjectConstructor, &VECTOR2(viewport.x / 2, viewport.y - 80));

    TextureGameObjectComp* ballTextureComp = NEW(TextureGameObjectComp);
    (*ballTextureComp) = (TextureGameObjectComp){.textureBrush = newTextureBrush(&COLOR_WHITE, "assets/textures/ball.png"), .size = VECTOR2(BALL_SIZE, BALL_SIZE)};
    GAMEOBJECT_ATTACH_COMP(ballGObject, TextureGameObjectComp, ballTextureComp);

    PhysicsGameObjectComp* ballPhysicsComp = NEW(PhysicsGameObjectComp);
    ballPhysicsComp->bounce = TRUE;
    ballPhysicsComp->bounciness = 1;
    GAMEOBJECT_ATTACH_COMP(ballGObject, PhysicsGameObjectComp, ballPhysicsComp);

    // Paddle
    GameObjectConstructor paddleGObjectConstructor = {.collisionType = COLLISION_BLOCK, .size = VECTOR2(100, 10), .objectType = OBJECT_MOVABLE};

    paddleGObject = level_spawnGameObject(&paddleGObjectConstructor, &VECTOR2(viewport.x / 2 - 50, viewport.y - 60));

    CubeGameObjectComp* paddleComp = NEW(CubeGameObjectComp);
    (*paddleComp) = (CubeGameObjectComp){.color = COLOR_GREEN, .size = VECTOR2(100, 10)};
    GAMEOBJECT_ATTACH_COMP(paddleGObject, CubeGameObjectComp, paddleComp);

    PhysicsGameObjectComp* paddlePhysicsComp = NEW(PhysicsGameObjectComp);
    GAMEOBJECT_ATTACH_COMP(paddleGObject, PhysicsGameObjectComp, paddlePhysicsComp);

    // UI
    initializeUI();

    initializeBlocks();
}

void initializeBlocks() {
    Vector2 viewport = renderer_getViewportSize();

    char levelPath[256], levelRow[256];
    strcat(levelPath, getExecutableFolderPath());
    strcat(levelPath, "/assets/levels/Level");

    switch (gameState.level) {
        case 1:
            strcat(levelPath, "1.txt");
            break;

        case 2:
            strcat(levelPath, "2.txt");
            break;

        default:
            return;
    }

    LOG("Loading level from: %s", levelPath);

    // Blocks
    GameObjectConstructor blockGObjectConstructor = {.collisionType = COLLISION_BLOCK, .size = VECTOR2(BLOCK_SIZE_X, BLOCK_SIZE_Y)};

    FILE* f = fopen(levelPath, "r");
    int row = 0, column = -1;
    char c;

    fgets(levelRow, sizeof(levelRow), f);
    int width = strlen(levelRow);

    fseek(f, 0, SEEK_SET);

    while ((c = getc(f)) != EOF) {
        column++;

        if (c == '0') continue;

        if (c == '\n') {
            column = -1;
            row++;
            continue;
        }

        GameObject* blockGObject = level_spawnGameObject(&blockGObjectConstructor, &VECTOR2((viewport.x / 2 - (BLOCK_SIZE_X * (width / 2))) + column * BLOCK_SIZE_X, TOP_WALL_OFFSET + BLOCK_SIZE_Y * 10 + row * BLOCK_SIZE_Y));

        TextureGameObjectComp* blockTextureComp = NEW(TextureGameObjectComp);
        (*blockTextureComp) = (TextureGameObjectComp){.textureBrush = newTextureBrush(&COLOR_RANDOM, "assets/textures/block.png"), .size = VECTOR2(BLOCK_SIZE_X, BLOCK_SIZE_Y)};
        GAMEOBJECT_ATTACH_COMP(blockGObject, TextureGameObjectComp, blockTextureComp);

        Block* block = NEW(Block);
        char healthStr[2] = {c, '\0'};
        (*block) = (Block){.gameObject = blockGObject, .health = atoi(healthStr)};

        LIST_ADD(blocks, Block*, block);
    }

    for (int i = 0; i < AMOUNT_OF_BLOCKS_X; i++) {
        for (int j = 0; j < AMOUNT_OF_BLOCKS_Y; j++) {
        }
    }
}

void initializeUI() {
    LOG("Initializing UI...");

    UICanvas* gameCanvas = level_createUICanvas();

    scoreText = NEW(TextUIComponent);
    (*scoreText) = (TextUIComponent){.id = 1, .position = VECTOR2(10, 10), .text = "Score: 0", .font = (Font){.size = 30, .path = "assets/fonts/AvrileSansUI-Regular.ttf", .color = COLOR_WHITE}};
    UICANVAS_ATTACH_COMP(gameCanvas, TextUIComponent, scoreText);

    livesText = NEW(TextUIComponent);
    (*livesText) = (TextUIComponent){.id = 2, .position = VECTOR2(10, 45), .text = "Lives: 3", .font = (Font){.size = 30, .path = "assets/fonts/AvrileSansUI-Regular.ttf", .color = COLOR_WHITE}};
    UICANVAS_ATTACH_COMP(gameCanvas, TextUIComponent, livesText);
}

void windowResized(Vector2* newSize) {
    cameraGObject->location.y = newSize->y / 2;
}

void event_ball_hit(GameObject* ballCollision, GameObject* collidedWith, Vector2* direction) {
    sound_play2D("assets/sounds/wallBang.wav", 0);

    int blockIndex = LIST_FIND_INDEX(blocks, Block*, ->gameObject, collidedWith);
    if (blockIndex != -1) {
        Block* b = blocks.items[blockIndex];
        b->health--;

        gameState_change(gameState.score + 1, gameState.lives);

        switch (b->health) {
            case 2:
                textureGameObjectComp_changeTexture(b->gameObject->components.items[0], "assets/textures/block_crack1.png");
                break;

            case 1:
                textureGameObjectComp_changeTexture(b->gameObject->components.items[0], "assets/textures/block_crack3.png");

            default:
                break;
        }

        if (blocks.items[blockIndex]->health <= 0) {
            LOG("Amount of game objects: %d", getLevel()->allGameObjects.size);
            level_destroyGameObject(collidedWith);
            LOG("Amount of game objects: %d", getLevel()->allGameObjects.size);
            LIST_REMOVE_CLEAN(blocks, Block*, blockIndex);

            if (blocks.size == 0) {
                LOG("You win!");
                gameState.playing = 0;

                engineCore_loadLevel(&WinLevel);
                //   You win
            }
        }
        return;
    }
}

void event_ball_beginOverlap(GameObject* self, GameObject* collidedWith) {
    if (collidedWith == bottomVoidGObject) {
        gameState_change(gameState.score, gameState.lives - 1);

        if (gameState.lives <= 0) {
            LOG("Game over!");
            engineCore_loadLevel(&LoseLevel);
        } else {
            gameState.playing = 0;

            Vector2 viewport = renderer_getViewportSize();
            ballGObject->location = VECTOR2(viewport.x / 2, viewport.y - 80);
            ballGObject->velocity = VECTOR2(0, 0);
        }
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
        else if (code == SDLK_SPACE && !gameState.playing) {
            LOG("Ball velocity: %d", gameState.ballSpeed);
            gameObject_setVelocity(ballGObject, &VECTOR2(gameState.ballSpeed * ((rand() % 2) ? -1 : 1), gameState.ballSpeed));
            gameState.playing = 1;
        }
    } else if (event->type == SDL_KEYUP) {
        if (code == SDLK_a && paddleGObject->velocity.x == -vel)
            paddleGObject->velocity.x = 0;
        else if (code == SDLK_d && paddleGObject->velocity.x == vel)
            paddleGObject->velocity.x = 0;
    }
}

void gameState_change(int score, int lives) {
    gameState.score = score;
    gameState.lives = lives;
    snprintf(scoreText->text, sizeof(scoreText->text), "Score: %d", score);
    snprintf(livesText->text, sizeof(livesText->text), "Lives: %d", lives);
}