#include "../include/tween.h"
#include <stdlib.h>
#include <SDL2/SDL.h>

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

void GM_DestroyTween (void* tween) {
    if (tween != NULL) {
        free((GM_Tween*)tween);
    }
}
