#include "../include/tween.h"
#include <stdlib.h>
#include <SDL2/SDL.h>

extern int FPS;
extern GM_List* gtween_list;

GM_Tween* GM_CreateTween (GM_Sprite* sprite, uint32_t duration, float end_x, float end_y) {
    GM_Tween* tween = malloc(sizeof(GM_Tween));
    tween->sprite = sprite;
    tween->begin_tm = SDL_GetTicks();
    tween->end_tm = tween->begin_tm+duration;
    tween->begin_x = sprite->x;
    tween->begin_y = sprite->y;
    tween->end_x = end_x;
    tween->end_y = end_y;
    return tween;
}

void GM_TriggerTween (GM_Tween* tween) {
    GM_Sprite* sprite = tween->sprite;
    printf("trigger tween\n");
    if (sprite != NULL && tween->end_tm != tween->begin_tm) {
        float off_x = (tween->end_x-tween->begin_x)/((tween->end_tm-tween->begin_tm)/(1000.f/FPS));
        float off_y = (tween->end_y-tween->begin_y)/((tween->end_tm-tween->begin_tm)/(1000.f/FPS));
        sprite->x += off_x;
        sprite->y += off_y;
    }
}

void GM_DestroyTween (void* tween) {
    printf("destroy tween\n");
    if (tween != NULL) {
        free((GM_Tween*)tween);
    }
}
