#pragma once

#include "level.h"

typedef struct GameState {
    int score;
    int lives;
    int ballSpeed;
    int level;
    int playing;
} GameState;

typedef struct Block {
    GameObject* gameObject;
    int health;
} Block;

DEFINE_LIST(AllBlocks, Block*);

DEFINE_LEVEL(GameLevel);

extern GameState gameState;

void initializeBlocks();
void initializeUI();
void windowResized(Vector2* newSize);
void event_ball_hit(GameObject* ballCollision, GameObject* collidedWith, Vector2* direction);
void event_ball_beginOverlap(GameObject* self, GameObject* collidedWith);
void event_anyInput(SDL_Event* event);
void gameState_change(int score, int lives);