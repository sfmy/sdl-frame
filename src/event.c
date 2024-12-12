#include "../include/event.h" 

GM_List* event_list = NULL;

void GM_CreateEventList ()  {
    event_list = GM_CreateList();
}

void GM_HandleEvent () {
    int quit = 0;
    SDL_Event e;
    GM_ListItem* item = NULL;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            for (item = event_list->first; item != NULL; item = item->next) {
                (*(GM_Event*)(item->data))(&e);
            }
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
        }
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
