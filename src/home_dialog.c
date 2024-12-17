#include "../include/home_dialog.h" 
#include "../include/event.h" 
#include <stdlib.h>
#include "../include/game.h"
#include "../include/audio.h"

HomeDialog *ghome_dialog = NULL;
extern TTF_Font *gfont;
extern GM_Sound *gclick_sound;

static void handleEvent (SDL_Event *e) {
    if (e->type == SDL_MOUSEBUTTONDOWN) {
        int x, y, n;
        SDL_GetMouseState(&x, &y);
        x = x-SCREEN_WIDTH/2.f;
        y = SCREEN_HEIGHT/2.f-y;
        for (n = 0; n < ghome_dialog->list_count; ++n) {
            if (GM_PointInSprite(x, y, ghome_dialog->level_list[n]->sprite)) {
                GM_PlaySound(gclick_sound);
                printf("click %d\n", ghome_dialog->level_list[n]->level);
                break;
            }
        }
    }
}

HomeLevelItem* GM_CreateHomeLevelItem () {
    HomeLevelItem *item = malloc(sizeof(HomeLevelItem));
    item->level = 0;
    item->sprite = NULL;
    return item;
}

void GM_DestroyHomeLevelItem (HomeLevelItem *item) {
    GM_DestroySprite(item->sprite);
    GM_DelListItemByData(gsprite_list, item->sprite);
    free(item);
}

void GM_CreateHomeDialog () {
    int i = 0;
    if (ghome_dialog == NULL) {
        ghome_dialog = malloc(sizeof(HomeDialog));
        ghome_dialog->page = 0;

        ghome_dialog->bg_sprite = GM_CreateSprite("res/home/Bg.png");
        GM_AddListItemByData(gsprite_list, ghome_dialog->bg_sprite);

        SDL_Color color = { 0xFF, 0xFF, 0xFF, 0xFF };
        ghome_dialog->level_label = GM_CreateLabel(gfont, "1/34", &color, 24);
        ghome_dialog->level_label->y = SCREEN_HEIGHT/2.f-50;
        GM_AddListItemByData(gsprite_list, ghome_dialog->level_label);

        ghome_dialog->list_count = 6;
        ghome_dialog->level_list = malloc(sizeof(HomeLevelItem*)*ghome_dialog->list_count);

        for (i = 0; i < ghome_dialog->list_count; ++i) {
            ghome_dialog->level_list[i] = GM_CreateHomeLevelItem();
        }
        GM_AddEvent((GM_Event)handleEvent);
    }
}

void GM_SetHomeDialogPage (int page) {
    int i, level;
    if (ghome_dialog != NULL) {
        ghome_dialog->page = page;
        char file[50] = {};
        for (i = 0; i < ghome_dialog->list_count; ++i) {
            level = i+page*ghome_dialog->list_count;
            sprintf(file, "res/levels/%d_up.png", level);
            ghome_dialog->level_list[i]->level = level; 
            if (ghome_dialog->level_list[i]->sprite != NULL) {
                GM_DestroySprite(ghome_dialog->level_list[i]->sprite);
                GM_DelListItemByData(gsprite_list, ghome_dialog->level_list[i]->sprite);
            }
            ghome_dialog->level_list[i]->sprite = GM_CreateSprite(file);
            GM_AddListItemByData(gsprite_list, ghome_dialog->level_list[i]->sprite);
            ghome_dialog->level_list[i]->sprite->x = (i%2 == 0)? -125:125;
            ghome_dialog->level_list[i]->sprite->y = 120-(int)(i/2)*180;
        }
    }
}

void GM_DestroyHomeDialog () {
    if (ghome_dialog != NULL) {
        int i;
        GM_DestroySprite(ghome_dialog->bg_sprite);
        GM_DestroySprite(ghome_dialog->level_label);
        GM_DelListItemByData(gsprite_list, ghome_dialog->bg_sprite);
        GM_DelListItemByData(gsprite_list, ghome_dialog->level_label);
        for (i = 0; i < ghome_dialog->list_count; ++i) {
            GM_DestroyHomeLevelItem(ghome_dialog->level_list[i]);
            ghome_dialog->level_list[i] = NULL;
        }
        GM_DelEvent((GM_Event)handleEvent);
        free(ghome_dialog->level_list);
        free(ghome_dialog);
        ghome_dialog = NULL;
    }
}
