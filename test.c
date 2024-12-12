#include "include/list.h"
#include "include/sprite.h" 
#include "include/game.h" 
#include <stdio.h> 

int main () {
    GM_List* sprite_list = GM_CreateList();
    GM_Sprite* sprite = GM_CreateSprite("text");
    sprite->z = 0;
    GM_AddListItem(sprite_list, sprite);

    sprite = GM_CreateSprite("text");
    sprite->z = 2;
    GM_AddListItem(sprite_list, sprite);

    sprite = GM_CreateSprite("text");
    sprite->z = 1;
    GM_AddListItem(sprite_list, sprite);

    GM_SortSpriteList(sprite_list);

    GM_ListItem* item = NULL;
    for (item = sprite_list->first; item != NULL; item = item->next) {
        printf("%f\n", ((GM_Sprite*)(item->data))->z);
    }
    return 0;
}
