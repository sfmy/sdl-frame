#ifndef LIST_H
#define LIST_H
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
void GM_AddListItem (GM_List* list, void* data);
void GM_DelListItem(GM_List* list, void* data);
void GM_FreeListData(GM_List* list, void (*fun) (void*));
void GM_DestroyList(GM_List* list);

#endif
