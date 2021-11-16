#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#define NODE struct contact
#define SIZE 26

/*
*****************************************************************
*
*       node implementation
*
*****************************************************************
*/

struct contact //Node of the linked list
{
    char name[20];
    char number[20];
    NODE *prev;
    NODE *next;
};

/*
*****************************************************************
*
*       global variables
*
*****************************************************************
*/

extern NODE *lists[SIZE]; //Array of linked lists
extern NODE *listsTail[SIZE]; //Array of linked lists' tails
extern char *fileHeader; //Header of the text file