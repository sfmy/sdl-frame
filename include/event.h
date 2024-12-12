#ifndef __event_h_
#define __event_h_
#include <SDL2/SDL.h>
#include "../include/list.h"

typedef void (* GM_Event) (SDL_Event*);
extern GM_List* event_list;

void GM_CreateEventList (); 
void GM_HandleEvent ();
void GM_AddEvent (GM_Event* e);
void GM_DelEvent (GM_Event* e);
void GM_DestroyEventList ();

#endif

