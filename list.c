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


// returns list of elements matching description
// specified by cmp function... Returns NULL if no element exists
Node *where(Node **head, bool (*cmp)(void *data), int size){

    // tracer for original list
    Node **tracer = head;

    // head of new list
    Node *headNewList = NULL;

    // tracer for new list
    Node **tracerNew = &headNewList;

    // loop through list
    while( *tracer ){

        // append to new list when appropriate
        if ( cmp((*tracer)->item->data) ){
            append(tracerNew, (*tracer)->item->data, size);
            tracerNew = &(*tracerNew)->next;
        }
        tracer = &(*tracer)->next;
    }

    return headNewList;

}

Node *findOne(Node **head, bool (*eq)(void *data)){

    Node **tracer =  head;
    while ( *tracer ){
        if (eq( (*tracer)->item->data )){
            return *tracer;
        }
        tracer = &(*tracer)->next;
    }
    return NULL;
}

// remove element at specific index
// we silently ignore calls with non existing index
void removeIndex(Node **head, int index){
    Node **tracer = head;
    int cnt = 0;

    // Try to loop to correct index
    while(*tracer && cnt < index){
        tracer = &(*tracer)->next;
        cnt++;
    }
    // if index exists we remove it
    if(*tracer){
        Node *tmp = *tracer;
        *tracer = (*tracer)->next;

        // Free memory
        free(tmp->item->data);
        free(tmp->item);
        free(tmp);
    }
}


// Remove elements maching decription given by function eq
void removeWhen(Node **head, bool (*eq)(void *data)){

    Node **tracer = head;

    //loop through list
    while( *tracer ) {

        if (eq((*tracer)->item->data) ){
            //Remove element
            Node *tmp = *tracer;
            *tracer = (*tracer)->next;
            free(tmp->item->data);
            free(tmp->item);
            free(tmp);
        }else{
            //move to next element
            tracer = &(*tracer)->next;
        }
    }
}

