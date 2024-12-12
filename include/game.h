#ifndef __game_h_
#define __game_h_
#include <SDL2/SDL.h>
#include "list.h"

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern SDL_Window* gwindow;
extern SDL_Renderer* grender;
extern int FPS;

int GM_Init (const char* title, int screen_width, int screen_height);
void GM_SortSpriteList (GM_List* list);
void GM_RenderSpriteList (GM_List* list);
void GM_Destroy ();
void GM_SetFPS (int fps);

#endif
