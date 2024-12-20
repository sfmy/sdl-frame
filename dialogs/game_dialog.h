#ifndef __game_dialog_h_
#define __game_dialog_h_ 
#include "../include/sprite.h" 

typedef struct RightArea {
    float x, y, w, h;
} RightArea;

typedef struct GameDialog {
    int level;
    int right_count;
    int wrong_count;
    GM_Sprite *bg_sprite;
    GM_Sprite *back_sprite;
    GM_Sprite *up_sprite;
    GM_Sprite *down_sprite;
    GM_Sprite **circle_sprite_list;
    RightArea **right_area;
} GameDialog;

extern GameDialog *ggame_dialog;
void GM_CreateGameDialog (int level);
void GM_DestroyGameDialog ();
#endif 

