#include "testLevel.h"

#include "BeEngine.h"
#include "borderUIComponent.h"
#include "buttonUIComponent.h"
#include "physicsGameObjectComp.h"
#include "textUIComponent.h"
#include "textureGameObjectComp.h"
#include "uiCanvas.h"

GameObject *go1,
    *go2, *go3;
// TODO: Make this into DECLARE_LEVEL() macro
Level testLevel = {.id = 1, .name = "testLevel", .event_loaded = &_testLevel_loaded};
TextureGameObjectComp saddam;

GameObject *player;
PhysicsGameObjectComp test;
TextureGameObjectComp texture;
UICanvas *canvas;
ButtonUIComponent btn1;
BorderUIComponent border1;
ButtonStyle style;
TextUIComponent txt1;

void event_clicked(ButtonUIComponent *comp, UICanvas *canvas) {
    LOG_W("SIZE: %d", txt1.font.size);
    if (txt1.font.size == 50) {
        txt1.font.size = 10;
        strcpy(txt1.text, "Smol text o.o");
    } else {
        txt1.font.size = 50;
        strcpy(txt1.text, "Large text :O");
    }
}

void _testLevel_loaded() {
    GameObjectSpawn playerSpawn = {
        .objectType = OBJECT_MOVABLE,
        .collisionType = COLLISION_BLOCK,
        .size = VECTOR2(10, 10),
        .event_beginOverlap = &event_beginOverlap,
        .event_endOverlap = &event_endOverlap};

    player = level_spawnGameObject(&playerSpawn, &VECTOR2(100, 10));

    texture = (TextureGameObjectComp){.imagePath = "./assets/textures/saddam.png", .size = VECTOR2(10, 10)};

    GAMEOBJECT_ATTACH_COMP(player, PhysicsGameObjectComp, &test);
    GAMEOBJECT_ATTACH_COMP(player, TextureGameObjectComp, &texture);

    canvas = engineCore_registerUICanvas(&((UICanvas){.id = NEW_ID}));

    style = BUTTONSTYLE(newTextureBrush(&COLOR(255, 0, 0), NULL),
                        newTextureBrush(&COLOR(0, 255, 0), NULL),
                        newTextureBrush(&COLOR(0, 0, 255), NULL),
                        TEXTUREBRUSH_DEFAULT);
    btn1 = (ButtonUIComponent){.id = 123, .position = VECTOR2(1000, 100), .size = VECTOR2(100, 100), .style = style, .event_clicked = &event_clicked};
    txt1 = (TextUIComponent){.id = 120, .position = VECTOR2(10, 500), .font = (Font){.path = "./assets/fonts/AvrileSansUI-Regular.ttf", .size = 50, .color = COLOR_BLACK}, .text = "Large text"};
    border1 = (BorderUIComponent){.fillBrush = newTextureBrush(&COLOR_WHITE, NULL), .position = VECTOR2(10, 500), .size = VECTOR2(500, 100)};

    ATTACH_UICOMPONENT(ButtonUIComponent, &btn1, canvas);
    ATTACH_UICOMPONENT(BorderUIComponent, &border1, canvas);
    ATTACH_UICOMPONENT(TextUIComponent, &txt1, canvas);

    go1 = level_spawnGameObject(&((GameObjectSpawn){
                                    .size = VECTOR2(50, 100),
                                    .collisionType = COLLISION_OVERLAP,
                                    .event_draw = &drawTest}),
                                &VECTOR2(40, 40));

    go2 = level_spawnGameObject(&((GameObjectSpawn){
                                    .size = VECTOR2(200, 200),
                                    .event_draw = &drawTest,
                                    .collisionType = COLLISION_BLOCK}),
                                &VECTOR2(50, 50));

    go3 = level_spawnGameObject(&((GameObjectSpawn){
                                    .size = VECTOR2(356, 200),
                                    .collisionType = COLLISION_BLOCK}),
                                &VECTOR2(500, 100));

    saddam = (TextureGameObjectComp){.imagePath = "./assets/textures/saddam.png", .size = VECTOR2(356, 200)};
    GAMEOBJECT_ATTACH_COMP(go3, TextureGameObjectComp, &saddam);
}

void drawTest(GameObject *gameObject) {
    renderer_drawFillRectangle(&COLOR(0, 255, 0), &go1->location, &go1->size);
    renderer_drawFillRectangle(&COLOR(255, 255, 0), &go2->location, &go2->size);
}

// Přidávat pozici na ticku (Pak udělat physics systém kde stačí dát velocity).
// Podle keydown se nastaví velocity a výpočty se provedou v physicsEngine.c
void event_anyInput(SDL_Event *event) {
    SDL_Keycode code = event->key.keysym.sym;

    float vel = 100;

    if (event->type == SDL_KEYDOWN) {
        if (code == SDLK_a)
            player->velocity.x = -vel;
        else if (code == SDLK_d)
            player->velocity.x = vel;
        else if (code == SDLK_w)
            player->velocity.y = vel;
        else if (code == SDLK_s)
            player->velocity.y = -vel;
    } else if (event->type == SDL_KEYUP) {
        if (code == SDLK_a && player->velocity.x == -vel)
            player->velocity.x = 0;
        else if (code == SDLK_d && player->velocity.x == vel)
            player->velocity.x = 0;
        else if (code == SDLK_w && player->velocity.y == vel)
            player->velocity.y = 0;
        else if (code == SDLK_s && player->velocity.y == -vel)
            player->velocity.y = 0;
    }
}

void event_draw() {
    // renderer_drawFillRectangle(&COLOR(255, 0, 0), &player->location, &player->size);
}

void event_beginOverlap(GameObject *self, GameObject *collidedWith) {
    LOG("Begin overlap!");
}

void event_endOverlap(GameObject *self, GameObject *collidedWith) {
    LOG("End overlap!");
}