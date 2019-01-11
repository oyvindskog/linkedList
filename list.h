#ifndef LIST_H
#define LIST_H

#include <stdbool.h>



typedef struct Item{
    void *data;
}Item;

typedef struct Node {
    Item *item;
    struct Node *next;
    struct Node *previous;
} Node;

typedef struct List {
    Node *first;
    Node *last;
} List;

typedef enum Type {
    Integer,
    Float,
    StringType,
    PointType,
    MAX_TYPES
}Type;

List createList();

void *getElementAt(List *list, int index);

void add(List *list, void *data, int size);

void addArray(List *list, void **data, int size, int count);

void print(List *list, Type type);

void freeList(List *list);

void sortList(List *list, Type type);

void sortT(List *list, bool (*cmp)(void *one, void *other));

void printT(List *list, void (*func)(void *data));

#endif // LIST_H
