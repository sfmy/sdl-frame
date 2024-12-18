#ifndef __home_dialog_h_
#define __home_dialog_h_
#include "../include/sprite.h"

typedef struct HomeLevelItem {
    int level;
    GM_Sprite *sprite;
} HomeLevelItem;

typedef struct HomeDialog {
    int cur_page, max_page;
    GM_Sprite *bg_sprite;
    GM_Sprite *left_arrow_sprite;
    GM_Sprite *right_arrow_sprite;
    GM_Sprite *level_label;
    HomeLevelItem **level_list;
    int list_count;
} HomeDialog;

extern HomeDialog *ghome_dialog;

HomeLevelItem* GM_CreateHomeLevelItem ();
void GM_DestroyHomeLevelItem (HomeLevelItem *item);
void GM_CreateHomeDialog ();
void GM_SetHomeDialogPage (int page);
void GM_SetHomeLevelItem (HomeLevelItem *item, int level);
void GM_DestroyHomeDialog ();

#endif
