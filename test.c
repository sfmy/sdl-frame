#include "include/list.h"
#include "include/sprite.h" 
#include "include/game.h" 
#include "include/audio.h"
#include <SDL2/SDL.h>
#include "include/event.h"
#include "dialogs/login_dialog.h"

extern GM_List* gsprite_list;
GM_Music* music = NULL;
TTF_Font* gfont = NULL;
SDL_Color color = { 0xFF, 0, 0, 0xFF };
GM_Sound *gclick_sound = NULL;

void init () {
    GM_Init("sdl window", 480, 720);
    GM_SetFPS(60);
    music = GM_CreateMusic("res/bgm.mp3", 1);
    gclick_sound = GM_CreateSound("res/click.mp3", 1);
    const char* font_file = "res/kaishu.ttf";
    gfont = TTF_OpenFont(font_file, 24);
    if (gfont == NULL) {
        printf("open gfont %s fail %s\n", font_file, TTF_GetError());
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

    GM_CreateLoginDialog();

    /* GM_AddEvent((GM_Event)handleEvent); */
    /* GM_AddEvent((GM_Event)handleEvent2); */

    GM_HandleEvent();

    GM_FreeMusic(music);
    GM_FreeSound(gclick_sound);
    GM_Destroy();
    return 0;
}
