#include "../include/sprite.h" 
#include <stdlib.h> 
#include <SDL2/SDL_image.h>

extern SDL_Renderer* grender;

GM_Sprite* GM_CreateSprite (const char* file_name) {
    GM_Sprite* sprite = malloc(sizeof(GM_Sprite));
    sprite->x = 0;
    sprite->y = 0;
    sprite->z = 0;
    sprite->w = 0;
    sprite->h = 0;
    sprite->label = file_name;
    sprite->texture = NULL;
    SDL_Surface* tmp = IMG_Load(file_name);
    if (tmp == NULL) {
        printf("load image %s fail %s\n", file_name, IMG_GetError());
    }
    else {
        sprite->texture = SDL_CreateTextureFromSurface(grender, tmp);
        if (sprite->texture == NULL) {
            printf("create image %s fail %s\n", file_name, SDL_GetError());
        }
        else {
            sprite->w = tmp->w; 
            sprite->h = tmp->h; 
        }
        SDL_FreeSurface(tmp);
    }
    return sprite;
}

GM_Sprite* GM_CreateLabel (TTF_Font* font, const char* label, SDL_Color* color, int size) {
    GM_Sprite* sprite = malloc(sizeof(GM_Sprite));
    sprite->x = 0;
    sprite->y = 0;
    sprite->z = 0;
    sprite->w = 0;
    sprite->h = 0;
    sprite->label = label;
    sprite->texture = NULL;
    TTF_SetFontSize(font, size);
    SDL_Surface* tmp = TTF_RenderText_Solid(font, label, *color);
    if (tmp == NULL) {
        printf("render text %s fail %s\n", label, TTF_GetError());
    }
    else {
        sprite->texture = SDL_CreateTextureFromSurface(grender, tmp);
        if (sprite->texture == NULL) {
            printf("create text %s fail %s\n", label, SDL_GetError());
        }
        else {
            sprite->w = tmp->w; 
            sprite->h = tmp->h; 
        }
        SDL_FreeSurface(tmp);
    }
    return sprite;
}

void GM_SetSpritePosition (GM_Sprite* gm_sprite, float x, float y) {
    gm_sprite->x = x;
    gm_sprite->y = y;
}

void GM_DestroySprite (GM_Sprite* gm_sprite) {
    if (gm_sprite->texture != NULL) {
        SDL_DestroyTexture(gm_sprite->texture);
        gm_sprite->texture = NULL;
    }
}
