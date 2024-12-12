#include "../include/list.h" 
#include <stdlib.h>
#include <stdio.h>


GM_List* GM_CreateList () {
    GM_List* list = malloc(sizeof(GM_List));
    list->first = NULL;
    list->last = NULL;
    list->length = 0;
    return list;
}

void GM_AddListItem (GM_List* list, void* data) {
    if (list == NULL) {
        printf("GM_AddListItem fail\n");
    }
    else {
        GM_ListItem* item = malloc(sizeof(GM_ListItem));
        item->data = data;
        if (list->length == 0) {
            list->first = item;
            list->last = item;
            item->pre = NULL;
            item->next = NULL;
        }
        else {
            list->last->next = item;
            item->pre = list->last;
            item->next = NULL;
            list->last = item;
        }
        ++ list->length;
    }
}

void GM_DelListItem(GM_List* list, void* data) {
    if (list == NULL) {
        printf("GM_DelListItem fail\n");
    }
    else {
        GM_ListItem* item = NULL;
        for (item = list->first; item != NULL; item = item->next) {
            if (item->data == data) {
                if (item->pre == NULL) {
                    list->first = item->next;
                }
                else {
                    item->pre->next = item->next;
                }
                free(item);
                -- list->length;
                break;
            }
        }
    }
}

void GM_FreeListData(GM_List* list, void (*fun) (void*)) {
    if (list == NULL) {
        printf("GM_FreeListData fail\n");
    }
    else {
        GM_ListItem* item = NULL;
        for (item = list->first; item != NULL; item = item->next) {
            if (item->data != NULL) {
                (*fun)(item->data);
                item->data = NULL;
            } 
        }
    }
}

void GM_DestroyList(GM_List* list) {
    if (list == NULL) {
        printf("GM_FreeListData fail\n");
    }
    else {
        GM_ListItem* item = list->first;
        GM_ListItem* tmp = NULL;
        while (item != NULL) {
            tmp = item->next;
            free(item);
            item = tmp;
        }
        free(list);
    }
}
