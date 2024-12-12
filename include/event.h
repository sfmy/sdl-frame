#ifndef __event_h_
#define __event_h_
#include <SDL2/SDL.h>

typedef void (* event)(SDL_Event*);

void createEvent (); 
int addEvent (event e);
int deleteEvent (event e);

#endif

