#include "../include/event.h" 
#include <stdio.h>
#include <stdint.h>
#include "../include/game.h"

extern int FPS;
extern GM_List* gevent_list;
void GM_HandleEvent () {
    int quit = 0;
    SDL_Event e;
    GM_ListItem* item = NULL;
    uint32_t start_tm = SDL_GetTicks();
    uint32_t delay_tm = 0;
    uint32_t cur_tm = 0;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            for (item = gevent_list->first; item != NULL; item = item->next) {
                ((GM_Event)(item->data))(&e);
            }
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
        }
        cur_tm = SDL_GetTicks();
        if (1000/FPS > (cur_tm-start_tm)) {
            delay_tm = 1000/FPS-(cur_tm-start_tm);
            SDL_Delay(delay_tm);
        }
        start_tm = SDL_GetTicks();
        GM_SortSpriteList();
        GM_RenderSpriteList();
    }
}

void GM_AddEvent (GM_Event e) {
    GM_AddListItem(gevent_list, e);
}

void GM_DelEvent (GM_Event e) {
    GM_DelListItem(gevent_list, e);
}

