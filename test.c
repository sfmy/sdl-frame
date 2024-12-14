#include "include/list.h"
#include "include/sprite.h" 
#include "include/game.h" 
#include "include/audio.h"
#include <SDL2/SDL.h>
#include "include/event.h"

extern GM_List* gsprite_list;
GM_Music* music = NULL;
TTF_Font* font = NULL;
SDL_Color color = { 0xFF, 0, 0, 0xFF };

void init () {
    GM_Init("sdl window", 400, 400);
    GM_SetFPS(60);
    music = GM_CreateMusic("res/bgm.mp3", 1);
    const char* font_file = "res/kaishu.ttf";
    font = TTF_OpenFont(font_file, 24);
    if (font == NULL) {
        printf("open font %s fail %s\n", font_file, TTF_GetError());
    }
}

void destroySprite (void* sprite) {
    GM_DestroySprite((GM_Sprite*)sprite);
}

void handleEvent (SDL_Event* e) {
    GM_Sprite* sprite = NULL;
    if (e->type == SDL_KEYDOWN) {
        if (e->key.keysym.sym == SDLK_h) {
            sprite = gsprite_list->last->data;
            sprite->x -= 1;
        }
        else if (e->key.keysym.sym == SDLK_l) {
            sprite = gsprite_list->last->data;
            sprite->x += 1;
        }
    }
    GM_RenderSpriteList();
}

void handleEvent2 (SDL_Event* e) {
    GM_Sprite* sprite = NULL;
    if (e->type == SDL_KEYDOWN) {
        if (e->key.keysym.sym == SDLK_j) {
            sprite = gsprite_list->last->data;
            sprite->y += 1;
        }
        else if (e->key.keysym.sym == SDLK_k) {
            sprite = gsprite_list->last->data;
            sprite->y -= 1;
        }
    }
    GM_RenderSpriteList();
}

int main () {
    init();
    GM_PlayMusic(music);

    GM_Sprite* sprite = GM_CreateSprite("res/red.png");
    GM_SetSpritePosition(sprite, 0, 0);
    sprite->z = 1;
    GM_AddSprite(sprite);

    sprite = GM_CreateSprite("res/blue.png");
    GM_SetSpritePosition(sprite, 40, 40);
    sprite->z = 2;
    GM_AddSprite(sprite);

    sprite = GM_CreateSprite("res/red2.png");
    GM_SetSpritePosition(sprite, 40, 40);
    sprite->z = 0;
    GM_AddSprite(sprite);

    sprite = GM_CreateLabel(font, "this is a test!", &color, 24);
    GM_SetSpritePosition(sprite, 20, 20);
    GM_AddSprite(sprite);

    GM_AddEvent((GM_Event)handleEvent);
    GM_AddEvent((GM_Event)handleEvent2);

    GM_HandleEvent();

    GM_FreeMusic(music);
    GM_Destroy();
    return 0;
}
