#include "include/list.h"
#include "include/sprite.h" 
#include "include/game.h" 
#include <SDL2/SDL.h>
/* #include <stdio.h>  */

GM_List* sprite_list = NULL;

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
    }
}

int main () {
    GM_Init("sdl window", 320, 320);

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

    GM_SortSpriteList(sprite_list);
    GM_RenderSpriteList(sprite_list);
    handleEvent();

    GM_FreeListData(sprite_list, destroySprite);
    GM_Destroy();
    return 0;
}
