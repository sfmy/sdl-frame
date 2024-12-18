#ifndef __login_dialog_h_
#define __login_dialog_h_

#include "../include/list.h"
#include "../include/sprite.h" 

typedef struct LoginDialog {
    GM_Sprite* bg_sprite;
    GM_Sprite* login_sprite;
    GM_Sprite* logo_sprite;
} LoginDialog;

LoginDialog *glogin_dialog;

void GM_CreateLoginDialog ();
void GM_DestroyLoginDialog ();

#endif 
