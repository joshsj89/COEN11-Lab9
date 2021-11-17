#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "lab9.h"

#define NODE struct contact
#define SIZE 26

/*
*****************************************************************
*
*       functions implementation
*
*****************************************************************
*/

void characterInsert(char newName[20], char newNumber[20])
{
    NODE *temp, *new_node;

    if (((temp = (NODE *)malloc(sizeof(NODE))) == NULL) || ((new_node = (NODE *)malloc(sizeof(NODE))) == NULL))
    {//Allocate pointers
        printf("Malloc error...\n"); //Error given if pointers not allocated successfully
        exit(1);
    }

    int letterIndex;
    
    if ((int)*newName >= 65 && (int)*newName <= 90)
    {
        letterIndex = (int)*newName - 65;
    }

    else if ((int)*newName >= 97 && (int)*newName <= 122)
    {
        letterIndex = (int)*newName - 97;
    }

    else
    {
        printf("Name starts with an invalid character. Try again.\n");
        return;
    }
    
    temp = lists[letterIndex];

    strcpy(new_node->name, newName); //Copies inputted name to a new node
    strcpy(new_node->number, newNumber); //Copies inputted number to a new node
    

    if (lists[letterIndex] == NULL) //If the list is empty
    {
        lists[letterIndex] = listsTail[letterIndex] = new_node; //Makes the new node the head and tail
        new_node->prev = new_node->next = NULL;
        return;
    }
    
    else if (strcasecmp(temp->name, new_node->name) > 0) //If the inputted name comes before the first name on the list
    {
        new_node->next = lists[letterIndex]; //Makes the new node point to the first on the list
        new_node->prev = NULL; //Makes the new node point back to NULL
        new_node->next->prev = new_node; //Makes the node the new node now points to point back to it
        lists[letterIndex] = new_node; //Makes the new node the head
        return;
    }
    
    while (temp->next != NULL && (strcasecmp(temp->name, new_node->name) < 0)) //Continues to the next node when the inputted name comes after the first name on list and is not the last node
            temp = temp->next; //Moves a pointer down the list
    
    if (temp->next == NULL && strcasecmp(temp->name, new_node->name) != 0) //If the new node will be the tail and is not a duplicate
    {
        new_node->next = temp->next;
        new_node->prev = listsTail[letterIndex];
        listsTail[letterIndex]->next = new_node;
        listsTail[letterIndex] = new_node;
        return;
    }

    else if (strcasecmp(temp->name, new_node->name) > 0) //If the inputted name comes before the name being checked
    {
        new_node->next = temp;
        new_node->prev = temp->prev;
        temp->prev->next = new_node; 
        temp->prev = new_node;
        return;
    } //Puts the new node in between temp and the one before temp
    
    else if (temp != NULL && (strcasecmp(newName, temp->name) == 0)) //If the inputted name is already on the list
    {
        printf("Sorry, this name and/or number is already in the phonebook.\n");
        return;
    }
}

void insert() //Insert function
{
    char newName[20];
    printf("Type the name to add: ");
    scanf("%s", newName); //Inputted name
    
    char newNumber[20];
    printf("Type the number to add for %s: ", newName);
    scanf("%s", newNumber); //Inputted number
    
    characterInsert(newName, newNumber);
}

void characterDelete(char inputtedName[20]) //Checks if name is in the phonebook before deleting
{
    int letterIndex;
    
    if ((int)*inputtedName >= 65 && (int)*inputtedName <= 90)
    {
        letterIndex = (int)*inputtedName - 65;
    }

    else if ((int)*inputtedName >= 97 && (int)*inputtedName <= 122)
    {
        letterIndex = (int)*inputtedName - 97;
    }

    else
    {
        printf("Name starts with an invalid character. Try again.\n");
        return;
    }
    
    NODE *temp = lists[letterIndex];

    if (lists[letterIndex] == NULL) //If the list is empty
    {
        printf("Sorry, the name you want to delete is not in the phonebook.\n"); //Not all 26 lists may be empty
        return;
    }
    
    if (temp->next == NULL && strcasecmp(temp->name, inputtedName) == 0) //When the name to be deleted is the head and tail node
    {
        lists[letterIndex] = listsTail[letterIndex] = NULL;
        printf("%s has been deleted.\n", temp->name);
        return;
    }
    
    else if (strcasecmp(temp->name, inputtedName) == 0) //When the name to be deleted is in the head node
    {
        lists[letterIndex] = temp->next; //Makes what the head pointed to the new head
        lists[letterIndex]->prev = NULL;
        printf("%s has been deleted.\n", temp->name);
        return;
    }

    while (temp != NULL && (strcasecmp(temp->name, inputtedName) != 0)) //Continues to the next node until a name matches or until the end of the list
        temp = temp->next; //Moves a pointer down the list

    if (temp == NULL) //If the end of the list is reached without finding a name match
    {
        printf("Sorry, the name you want to delete is not in the phonebook.\n");
        return;
    }

    else if (temp == listsTail[letterIndex]) //If the name to be deleted is the tail
    {
        listsTail[letterIndex] = temp->prev;
        listsTail[letterIndex]->next = NULL;
        printf("%s has been deleted.\n", temp->name);
        return;
    }
    
    else
    {
        temp->prev->next = temp->next; //Makes the node before the deleted one point to the node following the deleted one
        temp->next->prev = temp->prev;
        printf("%s has been deleted.\n", temp->name);
    }
    
    free(temp); //Deallocates pointer
}

void delete() //Delete function
{
    char deletedName[20];
    printf("Enter the name you want to delete: ");
    scanf("%s", deletedName); //User inputs the name that is to be deleted

    characterDelete(deletedName);
}

void show() //Show All function
{
    NODE *n;

    int letterIndex;
    for (letterIndex = 0; letterIndex < SIZE; ++letterIndex)
    {
        n = lists[letterIndex];

        while (n != NULL) //While node is not null
        {
            printf("%s\t%s\n", n->name, n->number); //Prints the name and number of one node
            n = n->next; //Contiues to the next node
        }
    }
}

void show_letter() //Show Corresponding function
{
    int letterIndex;
    char letter;
    printf("Enter the letter: ");
    scanf(" %c", &letter);
    
    if ((int)letter >= 65 && (int)letter <= 90)
    {
        letterIndex = (int)letter - 65;
    }

    else if ((int)letter >= 97 && (int)letter <= 122)
    {
        letterIndex = (int)letter - 97;
    }

    else
    {
        printf("Invalid character entered. Try again.\n");
        return;
    }

    NODE *n;

    if (lists[letterIndex] == NULL) //If the list is empty
        printf("The list of names beginning with %c is empty.\n", letter);
    
    n = lists[letterIndex];

    while (n != NULL) //While node is not null
    {
        printf("%s\t%s\n", n->name, n->number); //Prints the name and number of one node
        n = n->next; //Contiues to the next node
    }
}

void reverse(NODE *p, int index) //Reverse function
{
    NODE *temp;
    if ((temp = (NODE *)malloc(sizeof(NODE))) == NULL)
    {//Allocate pointers
        printf("Malloc error...\n"); //Error given if pointers not allocated successfully
        exit(1);
    }
    
    if (p == NULL) //If there are no nodes (Base case)
            return;

    else //If there are any nodes
    {//Switch prev and next pointers
        temp = p->prev; 
        p->prev = p->next; 
        p->next = temp;
        reverse(p->prev, index); //Continue to next node
        if (p->prev == NULL) //If the last node has been reached
            lists[index] = p; //then that last node will become the head
    }
}