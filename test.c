#include "include/list.h"
#include "include/sprite.h" 
#include "include/game.h" 
#include "include/audio.h"
#include <SDL2/SDL.h>
/* #include <stdio.h>  */

GM_List* sprite_list = NULL;
GM_Music* music = NULL;
TTF_Font* font = NULL;
SDL_Color color = { 0xFF, 0, 0, 0xFF };

void destroySprite (void* sprite) {
    GM_DestroySprite((GM_Sprite*)sprite);
}

void handleEvent () {
    int quit = 0;
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
        }
        GM_RenderSpriteList(sprite_list);
    }
}

int main () {
    GM_Init("sdl window", 400, 400);

    music = GM_CreateMusic("./res/bgm.mp3", 1);
    GM_PlayMusic(music);

    const char* font_file = "./res/玄冬楷书.ttf";
    font = TTF_OpenFont(font_file, 24);
    if (font == NULL) {
        printf("open font %s fail %s\n", font_file, TTF_GetError());
    }

    sprite_list = GM_CreateList();
    GM_Sprite* sprite = GM_CreateSprite("./res/red.png");
    GM_SetSpritePosition(sprite, 0, 0);
    sprite->z = 0;
    GM_AddListItem(sprite_list, sprite);

    sprite = GM_CreateSprite("./res/blue.png");
    GM_SetSpritePosition(sprite, 40, 40);
    sprite->z = 2;
    GM_AddListItem(sprite_list, sprite);

    sprite = GM_CreateSprite("./res/red2.png");
    GM_SetSpritePosition(sprite, 40, 40);
    sprite->z = 1;
    GM_AddListItem(sprite_list, sprite);

    sprite = GM_CreateLabel(font, "哈哈 this is a test!", &color, 24);
    GM_SetSpritePosition(sprite, 20, 20);
    GM_AddListItem(sprite_list, sprite);

    GM_SortSpriteList(sprite_list);
    handleEvent();

    GM_FreeListData(sprite_list, destroySprite);
    GM_DestroyList(sprite_list);
    GM_FreeMusic(music);
    GM_Destroy();
    return 0;
}
