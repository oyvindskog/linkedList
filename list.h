#ifndef LIST_H
#define LIST_H

#include <stdbool.h>

/**
 * Generic linked list
 */

typedef struct Item{
    void *data;
}Item;

typedef struct Node {
    Item *item;
    struct Node *next;
} Node;

void *getElementAt(Node **head, int index);


void append(Node **head, void *data, int size);

void prepend(Node **head, void *data, int size);

void appendArray(Node **head, void **data, int size, int count);

void freeList(Node **head);

int count(Node **head);

void sort(Node **head, bool (*cmp)(void *one, void *other));

void foreach(Node **head, void (*func)(void *data));

#endif // LIST_H
