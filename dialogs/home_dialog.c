#include "home_dialog.h" 
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
        if (GM_PointInSprite(x, y, ghome_dialog->left_arrow_sprite)) {
            if (ghome_dialog->cur_page == 0) {
                ghome_dialog->cur_page = ghome_dialog->max_page;
            }
            else {
                -- ghome_dialog->cur_page;
            }
            GM_SetHomeDialogPage(ghome_dialog->cur_page);
            return;
        }
        if (GM_PointInSprite(x, y, ghome_dialog->right_arrow_sprite)) {
            if (ghome_dialog->cur_page == ghome_dialog->max_page) {
                ghome_dialog->cur_page = 0;
            }
            else {
                ++ ghome_dialog->cur_page;
            }
            GM_SetHomeDialogPage(ghome_dialog->cur_page);
            return;
        }
        for (n = 0; n < ghome_dialog->list_count; ++n) {
            if (GM_PointInSprite(x, y, ghome_dialog->level_list[n]->sprite)) {
                GM_PlaySound(gclick_sound);
                printf("click %d\n", ghome_dialog->level_list[n]->level);
                return;
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
    float arrow_y = SCREEN_HEIGHT/2.f-50;
    if (ghome_dialog == NULL) {
        ghome_dialog = malloc(sizeof(HomeDialog));
        ghome_dialog->cur_page = 0;
        ghome_dialog->max_page = 10; // TODO

        ghome_dialog->bg_sprite = GM_CreateSprite("res/home/Bg.png");
        GM_AddListItemByData(gsprite_list, ghome_dialog->bg_sprite);

        ghome_dialog->left_arrow_sprite = GM_CreateSprite("res/home/Left.png");
        ghome_dialog->left_arrow_sprite->x = -100.f; 
        ghome_dialog->left_arrow_sprite->y = arrow_y; 
        GM_AddListItemByData(gsprite_list, ghome_dialog->left_arrow_sprite);

        ghome_dialog->right_arrow_sprite = GM_CreateSprite("res/home/Right.png");
        ghome_dialog->right_arrow_sprite->x = 100.f; 
        ghome_dialog->right_arrow_sprite->y = arrow_y; 
        GM_AddListItemByData(gsprite_list, ghome_dialog->right_arrow_sprite);

        ghome_dialog->level_label = NULL;

        /* SDL_Color color = { 0x0, 0x0, 0x0, 0xFF };
        ghome_dialog->level_label = GM_CreateLabel(gfont, "1/34", &color, 24);
        ghome_dialog->level_label->y = arrow_y;
        GM_AddListItemByData(gsprite_list, ghome_dialog->level_label); */

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
    float arrow_y = SCREEN_HEIGHT/2.f-50;
    if (ghome_dialog != NULL) {
        ghome_dialog->cur_page = page;
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
            ghome_dialog->level_list[i]->sprite->x = (i%2 == 0)? -100:100;
            ghome_dialog->level_list[i]->sprite->y = 120-(int)(i/2)*180;
            ghome_dialog->level_list[i]->sprite->scale.x = 0.8; 
            ghome_dialog->level_list[i]->sprite->scale.y = 0.8; 
        }
        if (ghome_dialog->level_label != NULL) {
            GM_DestroySprite(ghome_dialog->level_label);
            GM_DelListItemByData(gsprite_list, ghome_dialog->level_label);
        }
        SDL_Color color = { 0x0, 0x0, 0x0, 0xFF };
        sprintf(file, "%d/%d", ghome_dialog->cur_page, ghome_dialog->max_page);
        ghome_dialog->level_label = GM_CreateLabel(gfont, file, &color, 24);
        ghome_dialog->level_label->y = arrow_y;
        GM_AddListItemByData(gsprite_list, ghome_dialog->level_label);
    }
}

void GM_DestroyHomeDialog () {
    if (ghome_dialog != NULL) {
        int i;
        GM_DestroySprite(ghome_dialog->bg_sprite);
        GM_DestroySprite(ghome_dialog->level_label);
        GM_DestroySprite(ghome_dialog->left_arrow_sprite);
        GM_DestroySprite(ghome_dialog->right_arrow_sprite);
        GM_DelListItemByData(gsprite_list, ghome_dialog->bg_sprite);
        GM_DelListItemByData(gsprite_list, ghome_dialog->level_label);
        GM_DelListItemByData(gsprite_list, ghome_dialog->left_arrow_sprite);
        GM_DelListItemByData(gsprite_list, ghome_dialog->right_arrow_sprite);
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
