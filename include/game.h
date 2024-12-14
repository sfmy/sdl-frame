#ifndef __game_h_
#define __game_h_
#include <SDL2/SDL.h>
#include "sprite.h"
#include "list.h"

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern SDL_Window* gwindow;
extern SDL_Renderer* grender;
extern GM_List* gsprite_list;
extern GM_List* gevent_list;
extern GM_List* gtween_list;
extern int FPS;

int GM_Init (const char* title, int screen_width, int screen_height);
void GM_AddSprite (GM_Sprite* sprite);
void GM_SortSpriteList ();
void GM_RenderSpriteList ();
void GM_Destroy ();
void GM_SetFPS (int fps);

#endif
