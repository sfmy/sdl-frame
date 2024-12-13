#include "include/list.h"
#include "include/sprite.h" 
#include "include/game.h" 
#include "include/audio.h"
#include <SDL2/SDL.h>
#include "include/event.h"

#if __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif

GM_List* sprite_list = NULL;
GM_Music* music = NULL;
TTF_Font* font = NULL;
SDL_Color color = { 0xFF, 0, 0, 0xFF };

void init () {
    GM_Init("sdl window", 400, 400);
    GM_SetFPS(60);
    sprite_list = GM_CreateList();
    music = GM_CreateMusic("res/bgm.mp3", 1);
    const char* font_file = "res/kaishu.ttf";
    font = TTF_OpenFont(font_file, 24);
    if (font == NULL) {
        printf("open font %s fail %s\n", font_file, TTF_GetError());
    }
    GM_CreateEventList();
}

void destroySprite (void* sprite) {
    GM_DestroySprite((GM_Sprite*)sprite);
}

void handleEvent (SDL_Event* e) {
    GM_Sprite* sprite = NULL;
    if (e->type == SDL_KEYDOWN) {
        if (e->key.keysym.sym == SDLK_h) {
            sprite = sprite_list->last->data;
            sprite->x -= 1;
        }
        else if (e->key.keysym.sym == SDLK_l) {
            sprite = sprite_list->last->data;
            sprite->x += 1;
        }
    }
    GM_RenderSpriteList(sprite_list);
}

void handleEvent2 (SDL_Event* e) {
    GM_Sprite* sprite = NULL;
    if (e->type == SDL_KEYDOWN) {
        if (e->key.keysym.sym == SDLK_j) {
            sprite = sprite_list->last->data;
            sprite->y += 1;
        }
        else if (e->key.keysym.sym == SDLK_k) {
            sprite = sprite_list->last->data;
            sprite->y -= 1;
        }
    }
    GM_RenderSpriteList(sprite_list);
}

int main () {
    init();
    GM_PlayMusic(music);

    GM_Sprite* sprite = GM_CreateSprite("res/red.png");
    GM_SetSpritePosition(sprite, 0, 0);
    sprite->z = 1;
    GM_AddListItem(sprite_list, sprite);

    sprite = GM_CreateSprite("res/blue.png");
    GM_SetSpritePosition(sprite, 40, 40);
    sprite->z = 2;
    GM_AddListItem(sprite_list, sprite);

    sprite = GM_CreateSprite("res/red2.png");
    GM_SetSpritePosition(sprite, 40, 40);
    sprite->z = 0;
    GM_AddListItem(sprite_list, sprite);

    sprite = GM_CreateLabel(font, "this is a test!", &color, 24);
    GM_SetSpritePosition(sprite, 20, 20);
    GM_AddListItem(sprite_list, sprite);

    GM_SortSpriteList(sprite_list);

    GM_Event fun_1 = handleEvent;
    GM_Event fun_2 = handleEvent2;
    GM_AddEvent(&fun_1);
    GM_AddEvent(&fun_2);
#if __EMSCRIPTEN__
    emscripten_set_main_loop(GM_HandleEvent, -1, 1);
#else
    GM_HandleEvent();
#endif


    GM_DestroyEventList();
    GM_FreeListData(sprite_list, destroySprite);
    GM_DestroyList(sprite_list);
    GM_FreeMusic(music);
    GM_Destroy();
    return 0;
}
