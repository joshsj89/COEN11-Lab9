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

/*
*****************************************************************
*
*       function declarations
*
*****************************************************************
*/

void characterInsert(char newName[20], char newNumber[20]);
void insert(); //Function declaration of Insert
void characterDelete(char inputtedName[20]);
void delete(); //Function declaration of Delete
void show(); //Function declaration of Show All
void show_letter(); //Function declaration of Show Corresponding
void read_file(char *name); //Function declaration of Read File
void save_file(char *name); //Function declaration of Save File
void read_binary(char *name); //Function declaration of Read Binary File
void save_binary(char *name); //Function declaration of Save Binary File
void reverse(NODE *c, int index); //Fuction declaration of Reverse