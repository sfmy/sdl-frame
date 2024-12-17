#include "../include/event.h" 
#include "../include/game.h"
#include <stdio.h>
#include <stdint.h>

extern int FPS;
extern GM_List* gevent_list;
extern GM_List* gtween_list;

void GM_HandleEvent () {
    int quit = 0;
    SDL_Event e;
    GM_ListItem* item = NULL;
    GM_ListItem* next = NULL;
    uint32_t start_tm = SDL_GetTicks();
    uint32_t delay_tm = 0;
    uint32_t cur_tm = 0;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            item = gevent_list->first;
            while (item != NULL) {
                /* 有可能，在执行时销毁自身，先提前保存下一个item */
                next = item->next; 
                ((GM_Event)(item->data))(&e);
                item = next;
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
        GM_TriggerTweenList();
        GM_RenderSpriteList();
    }
}

