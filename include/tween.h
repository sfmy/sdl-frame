#ifndef __tween_h_
#define __tween_h_
#include <stdint.h>
#include "list.h"
#include "sprite.h"

typedef struct GM_Tween {
    GM_Sprite* sprite;
    uint32_t begin_tm;
    uint32_t end_tm;
    float begin_x, begin_y, end_x, end_y;
} GM_Tween;

GM_Tween* GM_CreateTween (GM_Sprite* sprite, uint32_t duration, float end_x, float end_y);
void GM_DestroyTween (void* tween);
#endif
