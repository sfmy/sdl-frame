#ifndef __game_h_
#define __game_h_
#include <SDL2/SDL.h>
#include "sprite.h"
#include "event.h"
#include "tween.h"
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

void GM_AddEvent (GM_Event e);
void GM_DelEvent (GM_Event e);

void GM_AddTween (GM_Tween* tween);
void GM_DelTween (GM_Tween* tween);

void GM_SetFPS (int fps);

void GM_TriggerTweenList ();
void GM_Destroy ();

#endif
