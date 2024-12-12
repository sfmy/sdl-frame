#include "../include/game.h" 
#include "../include/sprite.h"
#include <stdio.h> 
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern SDL_Window* gwindow;
extern SDL_Renderer* grender;

int GM_Init (const char* title, int screen_width, int screen_height) {
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
            }
        }
    }
    return 1;
}

void GM_SortSpriteList (GM_List* list) {
    GM_ListItem* begin = NULL;
    GM_ListItem* cur = NULL;
    GM_ListItem* pre = NULL;

    for (begin = list->first; begin != NULL; begin = begin->next) {
        for (cur = begin->next; cur != NULL; cur = cur->next) {
            pre = cur->pre;
            if (((GM_Sprite*)(cur->data))->z < ((GM_Sprite*)(pre->data))->z) {
                cur->pre = pre->pre;
                pre->next = cur->next;
                cur->next = pre;
                pre->pre = cur;
                if (list->first == pre) {
                    list->first = cur;
                }
                if (list->last == cur) {
                    list->last = pre;
                }
            }
        }
    }
}

void GM_RenderSpriteList (GM_List* list) {
    GM_ListItem* item = NULL;
    GM_Sprite* sprite;
    SDL_RenderClear(grender);
    for (item = list->first; item != NULL; item = item->next) {
        if (item->data != NULL) {
            sprite = (GM_Sprite*)(item->data);
            SDL_Rect rect = { sprite->x, sprite->y, sprite->w, sprite->h };
            SDL_RenderCopy(grender, sprite->texture, NULL, &rect);
        }
    }
    SDL_RenderPresent(grender);
}

void GM_Destroy () {
    SDL_DestroyRenderer(grender);
    SDL_DestroyWindow(gwindow);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}
