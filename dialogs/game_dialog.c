#include "game_dialog.h" 
#include "home_dialog.h"
#include "../include//audio.h"
#include "../include/list.h"
#include "../include/game.h"
#include "../include/event.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define EDIT 0

extern GM_Sound *gclick_sound;
GameDialog *ggame_dialog = NULL;

static uint32_t showWinSprite (uint32_t inteval, void *data) {
    ggame_dialog->win_sprite = GM_CreateSprite("res/game/Win.png");
    ggame_dialog->win_sprite->y = 100; 
    ggame_dialog->win_sprite->w *= 0.3;
    ggame_dialog->win_sprite->h *= 0.3;
    GM_AddListItemByData(gsprite_list, ggame_dialog->win_sprite); 
    return 0;
}

static void clickSprite (float x, float y) {
#ifdef EDIT
    printf("click %f, %f\n", x, y);
#endif
    int i = 0, is_right = 0;
    RightArea *area = NULL;
    for (i = 0; i < ggame_dialog->wrong_count && !is_right; ++i) {
        area = ggame_dialog->right_area[i];
        if (area->check) {
            continue;
        }
        if (x > area->x-area->w/2.0f && x < area->x+area->w/2.0f && \
                y > area->y-area->h/2.0f && y < area->y+area->h/2.0f) {
            is_right = 1;
        }
#ifdef EDIT
        is_right = 1;
#endif
    }
    if (is_right && area != NULL) {
        if (area->check == 0) {
            // printf("right, %f, %f, %f, %f\n", area->x, area->y, area->w, area->h);
#ifdef EDIT
            area->x = x;
            area->y = y;
#endif
            ggame_dialog->right_count ++;
            if (area->up_sprite == NULL) {
                area->up_sprite = GM_CreateSprite("res/game/right.png");
                area->up_sprite->x = area->x+ggame_dialog->up_sprite->x;
                area->up_sprite->y = area->y+ggame_dialog->up_sprite->y;
                area->up_sprite->w *= 0.5f;
                area->up_sprite->h *= 0.5f;
                GM_AddListItemByData(gsprite_list, area->up_sprite);
            }
            if (area->down_sprite == NULL) {
                area->down_sprite = GM_CreateSprite("res/game/right.png");
                area->down_sprite->x = area->x+ggame_dialog->down_sprite->x;
                area->down_sprite->y = area->y+ggame_dialog->down_sprite->y;
                area->down_sprite->w *= 0.5f;
                area->down_sprite->h *= 0.5f;
                GM_AddListItemByData(gsprite_list, area->down_sprite);
            }
            area->check = 1;
            if (!ggame_dialog->win_sprite && ggame_dialog->right_count == ggame_dialog->wrong_count && !ggame_dialog->timer) {
                ggame_dialog->timer = SDL_AddTimer(2*1000, showWinSprite, NULL);
            }
        }
    }
    else {
        printf("wrong\n");
    }
}

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
            x -= ggame_dialog->up_sprite->x;
            y -= ggame_dialog->up_sprite->y;
            clickSprite(x, y);
        }
        else if (GM_PointInSprite(x, y, ggame_dialog->down_sprite)) {
            x -= ggame_dialog->down_sprite->x;
            y -= ggame_dialog->down_sprite->y;
            clickSprite(x, y);
        }
    }
}

static void setRightAreaData () {
    ggame_dialog->right_area = malloc(sizeof(RightArea*)*ggame_dialog->wrong_count);
    char line[100];
    char file_name[50];
    sprintf(file_name, "res/game/level%d/config.txt", ggame_dialog->level);
    FILE *file = fopen(file_name, "r");
    int index = 0;
    RightArea *area = NULL;
    char *token = NULL;
    while (fgets(line, sizeof(line)/sizeof(char), file) != NULL) {
        area = malloc(sizeof(RightArea));
        area->x = atof(strtok(line, ","));
        area->y = atof(strtok(NULL, ","));
        area->w = atof(strtok(NULL, ","));
        area->h = atof(strtok(NULL, ","));
        area->up_sprite = NULL;
        area->down_sprite = NULL;

        // area->up_sprite = GM_CreateSprite("res/game/right.png");
        // area->up_sprite->x = ggame_dialog->up_sprite->x+area->x; 
        // area->up_sprite->y = ggame_dialog->up_sprite->y+area->y; 
        // area->up_sprite->w *= 0.5f;
        // area->up_sprite->h *= 0.5f;
        // GM_AddListItemByData(gsprite_list, area->up_sprite);

        // area->down_sprite = GM_CreateSprite("res/game/right.png");
        // area->down_sprite->x = ggame_dialog->down_sprite->x+area->x; 
        // area->down_sprite->y = ggame_dialog->down_sprite->y+area->y; 
        // area->down_sprite->w *= 0.5f;
        // area->down_sprite->h *= 0.5f;
        // GM_AddListItemByData(gsprite_list, area->down_sprite);

        area->check = 0;
        ggame_dialog->right_area[index] = area;
        ++ index;
    }
    fclose(file);
}

static void delRightAreaData () {
    int i = 0; 
    GM_Sprite *sprite = NULL; 
    for (i = 0; i < ggame_dialog->wrong_count; ++i) {
        sprite = ggame_dialog->right_area[i]->up_sprite;
        if (sprite != NULL) {
            GM_DelListItemByData(gsprite_list, sprite);
            GM_DestroySprite(sprite);
            ggame_dialog->right_area[i]->up_sprite = NULL;
        }
        sprite = ggame_dialog->right_area[i]->down_sprite;
        if (sprite != NULL) {
            GM_DelListItemByData(gsprite_list, sprite);
            GM_DestroySprite(sprite);
            ggame_dialog->right_area[i]->down_sprite = NULL;
        }
        free(ggame_dialog->right_area[i]);
    }
    free(ggame_dialog->right_area);
}

void GM_CreateGameDialog (int level) {
    printf("level:%d\n", level);
    char file_path[50] = {'\0'};
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

        sprintf(file_path, "res/game/level%d/up.png", level);
        ggame_dialog->up_sprite = GM_CreateSprite(file_path);
        printf("width:%f, height:%f\n", ggame_dialog->up_sprite->w, ggame_dialog->up_sprite->h);
        ggame_dialog->up_sprite->w *= 0.5f;
        ggame_dialog->up_sprite->h *= 0.5f;
        ggame_dialog->up_sprite->y = ggame_dialog->up_sprite->h/2.f;
        GM_AddListItemByData(gsprite_list, ggame_dialog->up_sprite);

        sprintf(file_path, "res/game/level%d/down.png", level);
        ggame_dialog->down_sprite = GM_CreateSprite(file_path);
        ggame_dialog->down_sprite->w *= 0.5f;
        ggame_dialog->down_sprite->h *= 0.5f;
        ggame_dialog->down_sprite->y = -ggame_dialog->down_sprite->h/2.f;
        GM_AddListItemByData(gsprite_list, ggame_dialog->down_sprite);

        ggame_dialog->win_sprite = NULL;
        ggame_dialog->timer = 0;

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

        if (ggame_dialog->win_sprite) {
            GM_DestroySprite(ggame_dialog->win_sprite);
            GM_DelListItemByData(gsprite_list, ggame_dialog->win_sprite);
        }
        if (ggame_dialog->timer) {
            SDL_RemoveTimer(ggame_dialog->timer);
        }

        GM_DelEvent((GM_Event)handleEvent);
        free(ggame_dialog);
    }
    ggame_dialog = NULL;
}
