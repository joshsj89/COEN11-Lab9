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

void read_file(char *name) //Read File function
{
    FILE *fp; //File pointer
    char string_name[20];
    char string_number[20];

    fp = fopen(name, "r"); //Reading the file

    if (fp == NULL) //The file does not exist and will be created upon save
        return;

    fseek(fp, strlen(fileHeader), SEEK_SET); //Bypass the header of the text file

    while (fscanf(fp, "%s%s", string_name, string_number) == 2) //While the file pointer points to a name and number
    {
        characterInsert(string_name, string_number); //Inserts the name from the file
    }

    fclose(fp); //Closes file pointer
}

void save_file(char *name) //Save File function
{
    FILE *fp; //File pointer
    NODE *p;

    fp = fopen(name, "w"); //Writing to the file (overwriting)

    if (fp == NULL) //If file does not exist
    {
       printf("The file cannot be saved.\n");
       return; 
    }
    
    fprintf(fp, "%s" , fileHeader); //Print the header to the file

    int letterIndex;
    for (letterIndex = 0; letterIndex < SIZE; ++letterIndex) //Prints all the names on the list into the file
    {
        p = lists[letterIndex];

        while (p != NULL) //While node is not null
        {
            fprintf(fp, "%s\t%s\n", p->name, p->number); //Writes name and number from the node into the file
            p = p->next; //Contiues to the next node
        }
    }

    fclose(fp); //Closes file pointer
}

void read_binary(char *name) //Read Binary File function
{
    FILE *fp; //File pointer
    NODE *p; //temporary node to hold each node from file

    if ((p = (NODE *)malloc(sizeof(NODE))) == NULL)
    {
        printf("Malloc error...\n"); //Error given if pointers not allocated successfully
        exit(1);
    }
    
    fp = fopen(name, "rb"); //Reading the file

    if (fp == NULL) //The file does not exist and will be created upon save
        return;

    while (fread(p, sizeof(NODE), 1, fp) > 0) //Reads each node that was saved
        printf("%s\t%s\n", p->name, p->number); //Prints the name and number of the temporary node

    fclose(fp); //Closes file pointer
}

void save_binary(char *name) //Save Binary File function
{
    FILE *fp; //File pointer
    NODE *p; //temporary node to hold each node from file

    if ((p = (NODE *)malloc(sizeof(NODE))) == NULL)
    {
        printf("Malloc error...\n"); //Error given if pointers not allocated successfully
        exit(1);
    }

    fp = fopen(name, "wb"); //Writing to the file (overwriting)

    if (fp == NULL) //If file does not exist
    {
       printf("The file cannot be saved.\n");
       return; 
    }

    int letterIndex;
    for (letterIndex = 0; letterIndex < SIZE; ++letterIndex)
    {
        p = lists[letterIndex];
        
        while (p != NULL) //While node is not null
        {
            fwrite(p, sizeof(NODE), 1, fp); //Writes one node to the file
            p = p->next; //Contiues to the next node
        }
    }

    fclose(fp); //Closes file pointer
}