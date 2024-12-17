#ifndef __list_h_
#define __list_h_
typedef struct GM_ListItem {
    void * data;
    struct GM_ListItem* next;
    struct GM_ListItem* pre;
} GM_ListItem;

typedef struct GM_List {
    struct GM_ListItem* first;
    struct GM_ListItem* last;
    int length;
} GM_List;

GM_List* GM_CreateList ();
GM_ListItem* GM_AddListItemByData (GM_List* list, void* data);
void GM_DelListItemByData (GM_List* list, void* data);
void GM_DelListItem (GM_List* list, GM_ListItem* item);
void GM_FreeListData(GM_List* list, void (*fun) (void*));
void GM_DestroyList(GM_List* list);

#endif
