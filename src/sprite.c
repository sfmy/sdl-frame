#include "../include/sprite.h" 
#include <stdlib.h> 

GM_Sprite* GM_CreateSprite (const char* file_name) {
    GM_Sprite* sprite = malloc(sizeof(GM_Sprite));
    sprite->x = 0;
    sprite->y = 0;
    sprite->w = 0;
    sprite->h = 0;
    return sprite;
}

GM_Sprite* GM_CreateLabel (TTF_Font* font, const char* label, SDL_Color* color, int size) {
    GM_Sprite* sprite = malloc(sizeof(GM_Sprite));
    sprite->x = 0;
    sprite->y = 0;
    sprite->w = 0;
    sprite->h = 0;
    /* TODO */
    return sprite;
}

void GM_SetSpritePosition (GM_Sprite* gm_sprite, float x, float y) {
    gm_sprite->x = x;
    gm_sprite->y = y;
}

void GM_DestroySprite (GM_Sprite* gm_sprite) {
    if (gm_sprite->texture != NULL) {

    }
}
