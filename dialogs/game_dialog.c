#include "game_dialog.h" 
#include "home_dialog.h"
#include "../include//audio.h"
#include "../include/list.h"
#include "../include/game.h"
#include "../include/event.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

extern GM_Sound *gclick_sound;
GameDialog *ggame_dialog = NULL;

static void handleEvent (SDL_Event *e) {
    if (e->type == SDL_MOUSEBUTTONDOWN) {
        int x, y;
        SDL_GetMouseState(&x, &y);
        x = x-SCREEN_WIDTH/2.f;
        y = SCREEN_HEIGHT/2.f-y;
        if (GM_PointInSprite(x, y, ggame_dialog->back_sprite)) {
            GM_PlaySound(gclick_sound);
            GM_CreateHomeDialog();
            GM_SetHomeDialogPage(1);
            GM_DestroyGameDialog();
        }
        else if (GM_PointInSprite(x, y, ggame_dialog->up_sprite)) {
            // TODO
        }
        else if (GM_PointInSprite(x, y, ggame_dialog->down_sprite)) {
            // TODO
        }
    }
}

static void setRightAreaData () {
    ggame_dialog->right_area = malloc(sizeof(RightArea*)*ggame_dialog->wrong_count);
    char line[100];
    FILE *file = fopen("res/game/level1/config.txt", "r");
    int index = 0;
    RightArea *area = NULL;
    char *token = NULL;
    while (fgets(line, sizeof(line)/sizeof(char), file) != NULL) {
        area = malloc(sizeof(RightArea));
        area->x = atof(strtok(line, ","));
        area->y = atof(strtok(NULL, ","));
        area->w = atof(strtok(NULL, ","));
        area->h = atof(strtok(NULL, ","));
        ggame_dialog->right_area[index] = area;
        ++ index;
    }
    fclose(file);
}

static void delRightAreaData () {
    int i = 0; 
    for (i = 0; i < ggame_dialog->wrong_count; ++i) {
        free(ggame_dialog->right_area[i]);
    }
    free(ggame_dialog->right_area);
}

void GM_CreateGameDialog (int level) {
    if (ggame_dialog == NULL) {
        ggame_dialog = malloc(sizeof(GameDialog));
        ggame_dialog->level = level;
        ggame_dialog->right_count = 0;
        ggame_dialog->wrong_count = 10;


        ggame_dialog->bg_sprite = GM_CreateSprite("res/game/GameBg.png");
        GM_AddListItemByData(gsprite_list, ggame_dialog->bg_sprite);

        ggame_dialog->back_sprite = GM_CreateSprite("res/game/homeBtn.png");
        ggame_dialog->back_sprite->w *= 0.3f;
        ggame_dialog->back_sprite->h *= 0.3f;
        ggame_dialog->back_sprite->x = -SCREEN_WIDTH/2.f+10+ggame_dialog->back_sprite->w/2;
        ggame_dialog->back_sprite->y = SCREEN_HEIGHT/2.f-10-ggame_dialog->back_sprite->h/2;
        GM_AddListItemByData(gsprite_list, ggame_dialog->back_sprite);

        ggame_dialog->up_sprite = GM_CreateSprite("res/game/level1/up.png");
        ggame_dialog->up_sprite->w *= 0.5f;
        ggame_dialog->up_sprite->h *= 0.5f;
        ggame_dialog->up_sprite->y = ggame_dialog->up_sprite->h/2.f;
        GM_AddListItemByData(gsprite_list, ggame_dialog->up_sprite);

        ggame_dialog->down_sprite = GM_CreateSprite("res/game/level1/down.png");
        ggame_dialog->down_sprite->w *= 0.5f;
        ggame_dialog->down_sprite->h *= 0.5f;
        ggame_dialog->down_sprite->y = -ggame_dialog->down_sprite->h/2.f;
        GM_AddListItemByData(gsprite_list, ggame_dialog->down_sprite);

        setRightAreaData();

        GM_AddEvent((GM_Event)handleEvent);
    }
}

void GM_DestroyGameDialog () {
    if (ggame_dialog != NULL) {
        delRightAreaData();
        GM_DestroySprite(ggame_dialog->bg_sprite);
        GM_DelListItemByData(gsprite_list, ggame_dialog->bg_sprite);

        GM_DestroySprite(ggame_dialog->up_sprite);
        GM_DelListItemByData(gsprite_list, ggame_dialog->up_sprite);

        GM_DestroySprite(ggame_dialog->down_sprite);
        GM_DelListItemByData(gsprite_list, ggame_dialog->down_sprite);

        GM_DelEvent((GM_Event)handleEvent);
        free(ggame_dialog);
    }
    ggame_dialog = NULL;
}
