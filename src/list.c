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

GM_ListItem* GM_AddListItemByData (GM_List* list, void* data) {
    if (list == NULL) {
        printf("GM_AddListItemByData fail\n");
        return NULL;
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
        return item;
    }
}

void GM_DelListItemByData(GM_List* list, void* data) {
    if (list == NULL) {
        printf("GM_DelListItemByData fail\n");
    }
    else {
        GM_ListItem* item = NULL;
        for (item = list->first; item != NULL; item = item->next) {
            if (item->data == data) {
                GM_DelListItem(list, item);
                break;
            }
        }
    }
}

void GM_DelListItem (GM_List* list, GM_ListItem* item) {
    if (list->first == item) {
        list->first = item->next;
        if (item->next != NULL) {
            item->next->pre = NULL;
        }
    }
    else {
        if (item->pre != NULL) {
            item->pre->next = item->next;
        }
    }
    if (list->last == item) {
        list->last = item->pre;
        if (item->pre != NULL) {
            item->pre->next = NULL;
        }
    }
    else {
        if (item->next != NULL) {
            item->next->pre = item->pre;
        }
    }
    free(item);
    -- list->length;
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
