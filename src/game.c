#include "../include/game.h" 
#include "../include/sprite.h"
#include "../include/list.h"
#include "../include/tween.h"
#include <stdio.h> 
#include <stdint.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 960;
SDL_Window* gwindow = NULL;
SDL_Renderer* grender = NULL;
GM_List* gsprite_list = NULL;
GM_List* gevent_list = NULL;
GM_List* gtween_list = NULL;
int FPS = 60;

int GM_Init (const char* title, int screen_width, int screen_height) {
    SCREEN_WIDTH = screen_width;
    SCREEN_HEIGHT = screen_height;
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) < 0) {
        printf("sdl init fail %s\n", SDL_GetError());
        return 0;
    }
    else {
        gwindow = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, SDL_WINDOW_SHOWN);
        if (gwindow == NULL) {
            printf("sdl create window fail %s\n", SDL_GetError());
            return 0;
        }
        else {
            grender = SDL_CreateRenderer(gwindow, -1, SDL_RENDERER_ACCELERATED);
            if (grender == NULL) {
                printf("sdl create render fail %s\n", SDL_GetError());
                return 0;
            }
            else {
                SDL_SetRenderDrawColor(grender, 0xFF, 0xFF, 0xFF, 0xFF);
                int img_flags = IMG_INIT_PNG;
                if (!(IMG_Init(img_flags)&img_flags)) {
                    printf("sdl image init fail %s\n", IMG_GetError());
                    return 0;
                }
                if (TTF_Init() == -1) {
                    printf("ttf init fail %s\n", TTF_GetError());
                    return 0;
                }
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
                    printf("mixer init fail %s\n", Mix_GetError());
                    return 0;
                }
            }
        }
    }
    gsprite_list = GM_CreateList();
    gevent_list = GM_CreateList();
    gtween_list = GM_CreateList();
    return 1;
}

void GM_SortSpriteList () {
    GM_ListItem* begin = NULL;
    GM_ListItem* cur = NULL;
    GM_ListItem* pre = NULL;
    int sorted = 1;
    for (cur = gsprite_list->first; cur != NULL && sorted; cur = cur->next) {
        if (cur->next != NULL && ((GM_Sprite*)(cur->data))->z > ((GM_Sprite*)(cur->next->data))->z) {
            sorted = 0;
        }
    }
    if (!sorted) {
        for (begin = gsprite_list->first; begin != NULL; begin = begin->next) {
            for (cur = begin->next; cur != NULL; cur = cur->next) {
                pre = cur->pre;
                if (((GM_Sprite*)(cur->data))->z < ((GM_Sprite*)(pre->data))->z) {
                    if (gsprite_list->first == pre) {
                        gsprite_list->first = cur;
                    }
                    else {
                        pre->pre->next = cur;
                    }
                    if (gsprite_list->last == cur) {
                        gsprite_list->last = pre;
                    }
                    else {
                        cur->next->pre = pre;
                    }
                    cur->pre = pre->pre;
                    pre->next = cur->next;
                    cur->next = pre;
                    pre->pre = cur;
                }
            }
        }
    }
}

void GM_RenderSpriteList () {
    GM_ListItem* item = NULL;
    GM_Sprite* sprite;
    SDL_RenderClear(grender);
    SDL_Rect window_rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    for (item = gsprite_list->first; item != NULL; item = item->next) {
        if (item->data != NULL) {
            sprite = (GM_Sprite*)(item->data);
            SDL_Rect rect = { 
                SCREEN_WIDTH/2.f+sprite->x-sprite->w/2.f*sprite->scale.x,
                SCREEN_HEIGHT/2.f-sprite->y-sprite->h/2.f*sprite->scale.y,
                sprite->w*sprite->scale.x,
                sprite->h*sprite->scale.y 
            };
            SDL_RenderCopy(grender, sprite->texture, &window_rect, &rect);
        }
    }
    SDL_RenderPresent(grender);
}


void GM_AddEvent (GM_Event e) {
    GM_AddListItemByData(gevent_list, e);
}

void GM_DelEvent (GM_Event e) {
    GM_DelListItemByData(gevent_list, e);
}

void GM_AddTween (GM_Tween* tween) {
    GM_AddListItemByData(gtween_list, tween);
}

void GM_DelTween (GM_Tween* tween) {
    GM_DelListItemByData(gtween_list, tween);
}

void GM_TriggerTweenList () {
    GM_ListItem* cur = NULL;
    uint32_t now = 0;
    if (gtween_list != NULL) {
        now = SDL_GetTicks();
        cur = gtween_list->first;
        while (cur != NULL) {
            GM_TriggerTween((GM_Tween*)(cur->data));
            if (((GM_Tween*)(cur->data))->end_tm <= now) {
                GM_DestroyTween((GM_Tween*)(cur->data));
                if (gtween_list->last == cur) {
                    GM_DelListItem(gtween_list, cur);
                    cur = NULL;
                }
                else {
                    cur = cur->next;
                    GM_DelListItem(gtween_list, cur->pre);
                }
            }
            else {
                cur = cur->next;
            }
        }
    }
}

void GM_Destroy () {
    GM_FreeListData(gsprite_list, GM_DestroySprite);
    GM_DestroyList(gsprite_list);
    gsprite_list = NULL;
    GM_DestroyList(gevent_list);
    gevent_list = NULL;
    GM_FreeListData(gtween_list, GM_DestroyTween);
    GM_DestroyList(gtween_list);
    gtween_list = NULL;

    SDL_DestroyRenderer(grender);
    SDL_DestroyWindow(gwindow);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

void GM_SetFPS (int fps) {
    FPS = fps;
}
