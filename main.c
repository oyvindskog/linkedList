#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "list.h"

typedef struct Point{
    int x;
    int y;
}Point;


bool comparePoints(void *one, void *other){
    Point *p = (Point*) one;
    Point *p2 = (Point*) other;
    if (p->x > p2->x){
        printf("%d > %d\n",p->x, p->y);
        return true;
    }else if(p2->x > p->x){
        return false;
    }else{
        printf(" is %d>%d ?", p->y, p2->y);
        return (p->y > p2->y);
    }
}

void printPoint(void *data){
    Point *p = (Point*) data;
    printf("(%d, %d)\n", p->x, p->y);
}

int main()
{

    //create list of integers
    List list = createList();

    //add one integer
    int value =4;
    add(&list, &value, sizeof(int));
    value = 2;
    add(&list, &value, sizeof(int));

    //add array of integers
    int intArray[10] = {1,2,3,4,5,6,7,8,9,10};
    void **array = (void**) intArray;
    addArray(&list, array, sizeof(int), 10);

    // get element by index
    for(int i=0; i<10; i++){
        int number = *(int*) getElementAt(&list, i);
        printf("element at %d = %d\n",i , number);
    }

    // print whole list of integers
    print(&list, Integer);

    // sort list of integers
    sortList(&list, Integer);
    print(&list, Integer);

    // free allocated memory for list
    freeList(&list);

    // create list of floats
    List fList = createList();
    // add one value
    float f = 2.1;
    add(&fList, &f, sizeof(float));
    f = 2.5;
    add(&fList, &f, sizeof(float));

    // add array of floats
    float floatArray[12] = {1.1, 2.2, 3.3, 4.4, 0.009, 5.5, 6.6, 7.7, 8.8, 9.9, 10.0, 0.003,};
    array = (void**) floatArray;
    addArray(&fList, array, sizeof(float), 12);

    // print whole array
    print(&fList, Float);
    sortList(&fList, Float);
    print(&fList, Float);
    freeList(&fList);

    //list of points
    Point p;
    p.x = 2;
    p.y = 3;
    List pList = createList();
    add(&pList, &p, sizeof(Point));
    p.x = 5;
    p.y = 2;
    add(&pList, &p, sizeof(Point));
    p.x = 1;
    p.y = 2;
    add(&pList, &p, sizeof(Point));

    printf("\nprinting points\n");
    printT(&pList, printPoint);
    sortT(&pList, comparePoints);
    printf("printing sorted points\n");
    printT(&pList, printPoint);
    freeList(&pList);

    //list of strings
    char* str = "My string";
    int len = strlen(str) + 1;
    printf("length = %d\n", len);
    List sList = createList();
    add(&sList, &str, len * sizeof(char));
    str = "I really love burgers";
    len = strlen(str) + 1;
    add(&sList, &str, len * sizeof(char));
    print(&sList, StringType);
    void* strArray[4] = {"this is 1", "2 it is", "4", "last one is 5"};
    int max = 0;
    for (int i=0; i<4; i++){
        len = strlen(strArray[i]) +1;
        if (len > max) max = len;
    }
    printf("Max is %d", max);
    addArray(&sList, strArray, max * sizeof(char), 4);
    print(&sList, StringType);
    freeList(&sList);
}
