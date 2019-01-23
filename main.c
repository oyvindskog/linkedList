#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "minunit.h"
#include "list.h"

//counter for unit tests
int tests_run = 0;

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

bool intsLargerThanFive(void *data) {
    int value = *(int*) data;
    return (value > 5);
}

bool myString(void *data){
    char *str = *(char**) data;
    return (strcmp(str, "My string") == 0);
}


static char *appendArray_countIncrease(){
    Node *list = NULL;
    int initial = count(&list);
    int arr[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    void **array = (void**) arr;
    appendArray(&list, array, sizeof(int), 10);
    int increase = count(&list) - initial;
    mu_assert("Error: Increase not as expected after appendArray", increase == 10);
    freeList(&list);
    return 0;
}

static char *append_countIncrease(){
    Node *list = NULL;
    int initial = count(&list);
    for (int i=0; i<10; i++){
        int value = 1;
        append(&list, &value, sizeof(int));
    }
    int increase = count(&list) - initial;
    mu_assert("Error: Increase not as expected after append", increase == 10);
    freeList(&list);
    return 0;
}

static char *prepend_countIncrease(){
    Node *list = NULL;
    int initial = count(&list);
    for (int i=0; i<10; i++){
        int value = 1;
        append(&list, &value, sizeof(int));
    }
    int increase = count(&list) - initial;
    mu_assert("Error: Increase not as expected after prepend", increase == 10);
    freeList(&list);
    return 0;
}

static char *all_tests() {
    mu_run_test(append_countIncrease);
    mu_run_test(prepend_countIncrease);
    mu_run_test(appendArray_countIncrease);
    return 0;
}

int main()
{

    char *result = all_tests();
    if (result != 0) {
        printf("%s\n", result);
    }
    else {
        printf("ALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);



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
    removeIndex(&listOfInts, 11);

    foreach(&listOfInts, printInt);
    // get element by index
    int len = count(&listOfInts);
    for(int i=0; i<len-1; i++){
        int number = *(int*) getElementAt(&listOfInts, i);
        printf("element at %d = %d\n",i , number);
    }

    sort(&listOfInts, compareInts);
    foreach(&listOfInts, printInt);

    Node *ints = where(&listOfInts, intsLargerThanFive, sizeof(int) );
    printf("ints larger than 5\n");
    foreach(&ints, printInt);

    freeList(&ints);
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

    Node *n = findOne(&sList, myString);
    printf("found : %s ", *(char**) n->item->data);
    freeList(&sList);
}
