#include "../include/login_dialog.h" 
#include <stdlib.h>
#include "../include/event.h"
#include "../include/game.h"
#include "../include/home_dialog.h"
#include "../include/audio.h"

extern GM_List *gsprite_list;
extern int SCREEN_HEIGHT;
extern int SCREEN_WIDTH;
extern LoginDialog *glogin_dialog;
extern GM_Sound *gclick_sound;

static void handleEvent (SDL_Event *e) {
    if (e->type == SDL_MOUSEBUTTONDOWN) {
        int x, y;
        SDL_GetMouseState(&x, &y);
        x = x-SCREEN_WIDTH/2.f;
        y = SCREEN_HEIGHT/2.f-y;
        if (GM_PointInSprite(x, y, glogin_dialog->login_sprite)) {
            GM_PlaySound(gclick_sound);
            GM_DestroyLoginDialog();
            GM_CreateHomeDialog();
            GM_SetHomeDialogPage(0);
        }
    }
}

void GM_CreateLoginDialog () {
    glogin_dialog = malloc(sizeof(LoginDialog));

    glogin_dialog->bg_sprite = GM_CreateSprite("res/login/Bg.png");
    GM_AddListItemByData(gsprite_list, glogin_dialog->bg_sprite);

    glogin_dialog->login_sprite = GM_CreateSprite("res/login/Login.png");
    glogin_dialog->login_sprite->y = -(SCREEN_HEIGHT*2/6.f);
    GM_AddListItemByData(gsprite_list, glogin_dialog->login_sprite);

    glogin_dialog->logo_sprite = GM_CreateSprite("res/login/Logo.png");
    glogin_dialog->logo_sprite->y = SCREEN_HEIGHT/4.f;
    GM_AddListItemByData(gsprite_list, glogin_dialog->logo_sprite);
    GM_AddEvent((GM_Event)handleEvent);

}

void GM_DestroyLoginDialog () {
    if (glogin_dialog != NULL) {
        GM_DestroySprite(glogin_dialog->bg_sprite);
        GM_DestroySprite(glogin_dialog->logo_sprite);
        GM_DestroySprite(glogin_dialog->login_sprite);

        GM_DelListItemByData(gsprite_list, glogin_dialog->bg_sprite);
        GM_DelListItemByData(gsprite_list, glogin_dialog->logo_sprite);
        GM_DelListItemByData(gsprite_list, glogin_dialog->login_sprite);

        GM_DelEvent((GM_Event)handleEvent);
        free(glogin_dialog);
        glogin_dialog = NULL;
    }
}
