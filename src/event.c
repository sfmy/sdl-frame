#include "../include/event.h" 
#include <stdio.h>
#include <stdint.h>

extern int FPS;
GM_List* event_list = NULL;

void GM_CreateEventList ()  {
    event_list = GM_CreateList();
}

void GM_HandleEvent () {
    int quit = 0;
    SDL_Event e;
    GM_ListItem* item = NULL;
    uint32_t start_tm = SDL_GetTicks();
    uint32_t delay_tm = 0;
    uint32_t cur_tm = 0;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            for (item = event_list->first; item != NULL; item = item->next) {
                (*(GM_Event*)(item->data))(&e);
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
    }
}

void GM_AddEvent (GM_Event* e) {
    GM_AddListItem(event_list, e);
}

void GM_DelEvent (GM_Event* e) {
    GM_DelListItem(event_list, e);
}

void GM_DestroyEventList () {
    if (event_list != NULL) {
        GM_DestroyList(event_list);
    }
}
