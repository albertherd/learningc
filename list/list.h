typedef struct node {
    struct node *next;
    struct node *prev;
    void *data;
} node;

typedef struct list {
    node *first;
    node *last;
    unsigned long count;
} list;

typedef struct listIterator {
    node *next;
} listIterator;

list *listInit();
node *listPushItem(list *list, void *data);
void *listElementAt(list *list, unsigned long at);
void listRemoveAt(list *list, unsigned long at);
listIterator *listGetIterator(list *list);
void *listIteratorNextValue(listIterator *iterator);
int listContains(list *list, int (*containsFunc)(void*));

#define LIST_CONTAINS_ITEM 1
#define LIST_DOESNT_CONTAIN_ITEM 0


static node *getNode(list *list, unsigned long at);
static node *getNodeFromFirst(list *list, unsigned long at);
static node *getNodeFromLast(list *list, unsigned long at);