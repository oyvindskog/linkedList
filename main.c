#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "list.h"


/**
 * tests for generic linked list
 */

typedef struct Point{
    int x;
    int y;
}Point;


bool comparePoints(void *one, void *other){
    Point *p = (Point*) one;
    Point *p2 = (Point*) other;
    if (p->x > p2->x){
        return true;
    }else if(p2->x > p->x){
        return false;
    }else{
        return (p->y > p2->y);
    }
}

bool compareInts(void *one, void *other){
    int a = *(int*) one;
    int b = *(int*) other;
    return (a > b);
}

bool compareFloats(void *one, void *other){
    int a = *(int*) one;
    int b = *(int*) other;
    return (a > b);
}

bool compareStrings(void *one, void *other) {
    char* a = *(char**) one;
    char* b = *(char**) other;
    int value = strcmp(a, b);
    return (value > 0);
}

void printPoint(void *data){
    Point *p = (Point*) data;
    printf("(%d, %d)\n", p->x, p->y);
}

void printInt(void *data){
    int value = *(int*) data;
    printf("%d\n", value);
}

void printString(void *data){
    char* value = *(char**) data;
    printf("%s\n", value);
}

void printFloat(void *data){
    float value = *(float*) data;
    printf("%f\n", value);
}

int main()
{

    printf("lets go");
    // create List
    Node *listOfInts = NULL;
    //add one integer
    int value =4;
    prepend(&listOfInts, &value, sizeof(int));
    // append integer
    value = 2;
    append(&listOfInts, &value, sizeof(int));


    int intArray[10] = {1,2,3,4,5,6,7,8,9,10};
    void **array = (void**) intArray;
    appendArray(&listOfInts, array, sizeof(int), 10);

    foreach(&listOfInts, printInt);
    // get element by index
    int len = count(&listOfInts);
    for(int i=0; i<len-1; i++){
        printf("%d\n",i);
        int number = *(int*) getElementAt(&listOfInts, i);
        printf("element at %d = %d\n",i , number);
    }

    sort(&listOfInts, compareInts);
    foreach(&listOfInts, printInt);

    freeList(&listOfInts);




    Node *fList = NULL;      //List of floats
    float f = 2.1;
    append(&fList, &f, sizeof(float));
    f = 2.5;
    append(&fList, &f, sizeof(float));

    // add array of floats
    float floatArray[12] = {1.1, 2.2, 3.3, 4.4, 0.009, 5.5, 6.6, 7.7, 8.8, 9.9, 10.0, 0.003,};
    array = (void**) floatArray;
    appendArray(&fList, array, sizeof(float), 12);

    // print whole array
    foreach(&fList, printFloat);

    //sort list
    sort(&fList, compareFloats);
    foreach(&fList, printFloat);
    freeList(&fList);

    //list of points
    Node *pList = NULL;

    Point p;
    p.x = 2;
    p.y = 3;
    append(&pList, &p, sizeof(Point));
    p.x = 5;
    p.y = 2;
    append(&pList, &p, sizeof(Point));
    p.x = 1;
    p.y = 2;
    append(&pList, &p, sizeof(Point));

    printf("\nprinting points\n");
    foreach(&pList, printPoint);
    sort(&pList, comparePoints);
    printf("printing sorted points\n");
    //printT(&pList, printPoint);

    foreach(&pList, printPoint);
    printf("done printing sorted points\n");

    freeList(&pList);

    //list of strings
    char* str = "My string";
    len = strlen(str) + 1;

    Node *sList = NULL;
    append(&sList, &str, len * sizeof(char));
    str = "I really love burgers";
    len = strlen(str) + 1;
    prepend(&sList, &str, len * sizeof(char));

    // add array of strings
    void* strArray[5] = {"this is 1", "2 it is", "4", "last one is 5", "aaffa"};
    int cntChars = 0;
    for (int i=0; i<4; i++){
        cntChars += strlen(strArray[i]) +1;
    }

    appendArray(&sList, strArray, cntChars * sizeof(char), 4);
    foreach(&sList, printString);
    sort(&sList, compareStrings);

    foreach(&sList, printString);
    freeList(&sList);
}
