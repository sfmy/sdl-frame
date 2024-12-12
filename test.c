#include "list.h"
#include "game.h"
#include "texture.h"
#include "audio.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

const char* font_file = "./玄冬楷书.ttf";
const int STEP = 20;
void freeTextureList (void* texture) {
    if (texture != NULL) {
        GM_DestroyTexture((GM_Texture*)texture);
    }
}

int main (int argc, char ** argv) {
    GM_Init("game", 400, 400);
    GM_Texture* gm_texture = NULL;
    GM_Texture* blue_texture = NULL;
    GM_ListItem* item = NULL;
    GM_List* texture_list = GM_CreateList();
    TTF_Font* font = TTF_OpenFont(font_file, 24);
    SDL_Color color = { 0xFF, 0xFF, 0xFF };
    GM_Music* music = GM_CreateMusic("./bgm.mp3", 1);
    GM_PlayMusic(music);
    GM_Sound* click_sound = GM_CreateSound("./click.wav", 1);

    gm_texture = GM_CreateTexture("./white.png");
    gm_texture->z = 0;
    GM_SetTexturePosition(gm_texture, 0, 0);
    GM_AddListItem(texture_list, gm_texture);

    blue_texture = GM_CreateTexture("./blue.png");
    GM_SetTexturePosition(blue_texture, 0, 0);
    GM_AddListItem(texture_list, blue_texture);

    gm_texture = GM_CreateLabel(font, "this is a test", &color, 24);
    GM_SetTexturePosition(gm_texture, 0, -gm_texture->h);
    GM_AddListItem(texture_list, gm_texture);
    GM_SortTextureList(texture_list);
    SDL_Event e;
    int quit = 0;
    while (!quit) {
        GM_Render(texture_list);
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN) {
                GM_PlaySound(click_sound);
            }
            else if (e.type == SDL_KEYDOWN) { // left
                switch (e.key.keysym.sym) {
                    case SDLK_h:
                        printf("left\n");
                        blue_texture->x -= 20;
                        break;
                    case SDLK_LEFT:
                        printf("left\n");
                        blue_texture->x -= 20;
                        break;
                }
            }
        }
    }
    GM_FreeList(texture_list, freeTextureList);
    GM_DestroyList(texture_list);
    TTF_CloseFont(font);
    GM_FreeMusic(music);
    GM_FreeSound(click_sound);
    GM_Destroy();
}

