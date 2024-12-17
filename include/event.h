#ifndef __event_h_
#define __event_h_
#include <SDL2/SDL.h>
#include "../include/list.h"

typedef void (* GM_Event) (SDL_Event*);
void GM_HandleEvent ();

#endif

