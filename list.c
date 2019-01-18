#include <stdio.h>
#include <stdlib.h>
#include "list.h"

/**
 * Generic linked list
 */


/* get element with specific index
 * Result must be casted by caller to correct type
 * returns null if no such index exists
 */
void *getElementAt(Node **head, int index){

    Node **tracer = head;
    int cnt = 0;
    while (cnt < index){
        cnt++;
        tracer = &(*tracer)->next;
        if (*tracer == NULL){
            return NULL;
        }
    }
    return (*tracer)->item->data;
}

Item *createItem(void *data, int size){

    Item *item;
    item =(Item*) malloc(sizeof(struct Item));
    item->data = malloc(size);

    for (int i=0; i<size; i++){
        *(char *)(item->data + i) = *(char *)(data + i);
    }

    return item;
}

Node *createNode(){
    Node *newNode = (Node*) malloc(sizeof(struct Node));
    newNode->next = NULL;
    newNode->item = NULL;
    return newNode;
}

// insert new node into end of list
void append(Node **head, void *data, int size){
    Node **tracer = head;
    // Create new node
    Node *newNode = createNode();
    newNode->next = NULL;
    newNode->item = createItem(data, size);

    //loop to end of list
    while( *tracer ) {
        tracer = &(*tracer)->next;
    }

    *tracer = newNode;

}

/* Insert new node into front of list */
void prepend(Node **head, void *data, int size){

    Node **tracer = head;
    // Create new node
    Node *newNode = createNode();
    newNode->next = *tracer;
    newNode->item = createItem(data, size);

    *tracer = newNode;
}


void appendArray(Node **head, void **data, int size, int count){
    for (int i=0; i<count; i++){
        append(head, &data[i], size);
    }
}

void freeList(Node **head){
    Node **tracer = head;
    while (*tracer){
        Node *tmp = *tracer;
        *tracer = (*tracer)->next;
        free(tmp->item->data);
        free(tmp->item);
        free(tmp);
    }
}

// returns number of elements
int count(Node **head){
    Node **tracer = head;
    int cnt = 1;
    while (*tracer){
        cnt++;
        tracer = &(*tracer)->next;
    }
    return cnt;
}

/*
 * Sorting based on function cmp
 * using bubblesort for simplicity.
 */
void sort(Node **head, bool (*cmp)(void *one, void *other)){

    Node **tracer = head;
    int last = count(head) - 2;

    while (last > 0){
        tracer = head;
        int cnt = 0;
        while(cnt < last){
            //compare
            void *thisOne =  (*tracer)->item->data;
            void *nextOne = (*tracer)->next->item->data;
            if(cmp(thisOne, nextOne)){
                //Swap
                Item *tmp = (*tracer)->item;
                (*tracer)->item = (*tracer)->next->item;
                (*tracer)->next->item = tmp;
            }
            tracer = &(*tracer)->next;
            cnt++;
        }
        last--;
    }
}

void foreach(Node **head, void (*func)(void *data)){
    Node **tracer = head;
    while( *tracer ){
        func( (*tracer)->item->data );
        tracer = &(*tracer)->next;
    }
}

