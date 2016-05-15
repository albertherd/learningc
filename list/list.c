#include "list.h"
#include <stdio.h>
#include <stdlib.h>

list *listInit()
{
    list *newList;
    if((newList = malloc(sizeof(*newList))) == NULL)
    {
        return NULL;
    }
    
    newList->first = NULL;
    newList->last = NULL;
    newList->count = 0;  
    
    return newList; 
}

node *listPushItem(list *list, void *data)
{
    node *newItem;
    if((newItem = malloc(sizeof(*newItem))) == NULL)
    {
        return NULL;
    }
    
    newItem->data = data;   

    if(list->count == 0)
    {
        list->first = newItem;
        list->last = newItem;    
        newItem->next = NULL;
        newItem->prev = NULL; 
    }
    else
    {
        list->last->next = newItem;
        newItem->prev = list->last;
        newItem->next = NULL; 
        list->last = newItem;
    }
    
    list->count++;    
    
    return newItem;
}

void *listElementAt(list *list, unsigned long at)
{
    if(!list || at >= list->count)
    {
        return NULL;
    }
    
    return getNode(list, at)->data;
}

void listRemoveAt(list *list, unsigned long at)
{
    if(!list || at >= list->count)
    {
        return NULL;
    }
    
    node * toRemove = getNode(list, at);
    
    if(list->first == toRemove)
    {
        list->first = list->first->next;
        list->first->prev = NULL;
    }    
    else if(list->last == toRemove)
    {
        list->last = list->last->prev;
        list->last->next = NULL;
    }
    else
    {
        toRemove->prev->next = toRemove->next;
        toRemove->next->prev = toRemove->prev;
    }        
    
    free(toRemove);
    list->count--;
}

listIterator *listGetIterator(list *list)
{
    if(list == NULL || list->count == 0)
    {
        return NULL;
    }
    
    listIterator *iterator;
    if((iterator = malloc(sizeof(*iterator))) == NULL)
    {
        return NULL;
    }
    
    iterator->next = list->first;
    return iterator;
}


void *listIteratorNextValue(listIterator *iterator)
{
    if(!iterator->next)
    {
        return NULL;    
    }
    void *result = iterator->next->data;
    iterator->next = iterator->next->next;
    return result;    
}

int listContains(list *list, int (*containsFunc)(void*))
{
    listIterator *iterator = listGetIterator(list);
    void *item;
    while((item = listIteratorNextValue(iterator)) != NULL)
    {
        if(containsFunc(item))
        {
            return LIST_CONTAINS_ITEM;
        }
    }    
    
    return LIST_DOESNT_CONTAIN_ITEM;
}

static node *getNode(list *list, unsigned long at)
{
    unsigned long midpoint = list->count / 2;
    
    if(at > midpoint)
    {
       return getNodeFromLast(list, at);
    }
    else
    {
       return getNodeFromFirst(list, at);
    }
}

static node *getNodeFromFirst(list *list, unsigned long at)
{
    long curPos = 0;
    node * curNode = list->first;
    while(curPos != at)
    {
        curNode = curNode->next;
        curPos++;
    }
    return curNode;
}

static node *getNodeFromLast(list *list, unsigned long at)
{
    long curPos = (list->count - 1);
    node *curNode = list->last;
    while(curPos != at)
    {
        curNode = curNode->prev;
        curPos--;
    }
    return curNode;
}
