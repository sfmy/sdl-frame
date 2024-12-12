#ifndef __sprite_h_
#define __sprite_h_
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

typedef struct GM_Sprite {
    float x, y, z, w, h;
    SDL_Texture* texture;
} GM_Sprite;

GM_Sprite* GM_CreateSprite (const char* file_name);
GM_Sprite* GM_CreateLabel (TTF_Font* font, const char* label, SDL_Color* color, int size);
void GM_SetSpritePosition (GM_Sprite* gm_sprite, float x, float y);
void GM_DestroySprite (GM_Sprite* gm_sprite);
#endif