#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "list.h"

List createList(){
    List list;
    list.first = (Node*) malloc(sizeof(struct Node));
    list.first->next = NULL;
    list.first->previous = NULL;
    list.first->item = NULL;
    list.last = list.first;
    return list;
}

void *getElementAt(List *list, int index){
    if (list == NULL){
        return NULL;
    }
    Node *tmp = list->first;
    for (int i=0; i<index; i++){
        tmp = tmp->next;
        if (tmp == NULL){

            return NULL;
        }
    }
    return tmp->item->data;
}

void addInteger(List *list, int value){
    Node *current = list->first;
    while (current->next != NULL){
        current = current->next;
    }

    current->item =(Item*) malloc(sizeof(struct Item));
    current->item->data = (int*) malloc(sizeof(int));
    *(int*) current->item->data = value;
    printf("%d\n", *(int*) current->item->data);
    Node *tmp = (Node*)malloc(sizeof(struct Node));
    tmp->next = NULL;
    tmp->previous = current;
    tmp->item = NULL;
    current->next = tmp;
    list->last = tmp;
}

void add(List *list, void *data, int size){
    Node *current = list->first;
    while (current->next != NULL){
        current = current->next;
    }

    current->item =(Item*) malloc(sizeof(struct Item));
    current->item->data = malloc(size);

    for (int i=0; i<size; i++)
        *(char *)(current->item->data + i) = *(char *)(data + i);

    Node *tmp = (Node*)malloc(sizeof(struct Node));
    tmp->next = NULL;
    tmp->previous = current;
    tmp->item = NULL;
    current->next = tmp;
    list->last = tmp;
}

void addArray(List *list, void **data, int size, int count){
    for (int i=0; i<count; i++){
        add(list, &data[i], size);
    }
}


void freeList(List *list){
    Node *current = list->first;
    while (current->next != NULL){
        Node *tmp = current->next;
        free(current->item->data);
        free(current->item);
        free(current);
        current = tmp;
    }
}

void printInt(void *data){
    printf("\n%d", *(int*) data);
}

void printFloat(void *data){
    printf("\n%f", *(float*) data);
}

void printString(void *data){
    printf("\n%s", *(char**) data);
}

void printPoint(void *data){
    Point *p = (Point*) data;
    printf("(%d, %d)", p->x, p->y);
}

void print(List *list, Type type){

    void (*printType[MAX_TYPES]) (void* data);
    printType[Integer] = printInt;
    printType[Float] = printFloat;
    printType[StringType] = printString;
    printType[PointType] = printPoint;

    Node *current = list->first;
    while (current->next != NULL){
        printType[type](current->item->data);
        current = current->next;
    }
}

bool compareInts(void *one, void *other){
    return (*(int*) one > *(int*) other);
}
bool compareFloats(void *one, void *other){
    return (*(float*) one > *(float*) other);
}

void sortList(List *list, Type type){
    bool (*compare[MAX_TYPES]) (void* data, void *otherData);
    compare[Integer] = compareInts;
    compare[Float] = compareFloats;

    Node *last = list->last->previous; //last is dummy

    while (last->previous->previous != NULL){ //Stop on element 2
        Node *current = list->first;
        while(current != last){
            //compare
            void *thisOne =  current->item->data;
            void *nextOne = current->next->item->data;
            if(compare[type](thisOne, nextOne)){
                //Swap
                Item *tmp = current->item;
                current->item = current->next->item;
                current->next->item = tmp;
            }
            current = current->next;
        }
        last = last->previous;
    }
}
