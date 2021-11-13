/*
*****************************************************************
*
*       Lab 9   Phone Book      Reversible
*       COEN 11 -- Fall 2021
*
*****************************************************************
*/
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

NODE *lists[SIZE]; //Array of linked lists
NODE *listsTail[SIZE]; //Array of linked lists' tails
char *fileHeader = "Names\tNumbers\t\n\n----------------------------------\n\n"; //Header of the text file

/*
*****************************************************************
*
*       function declarations
*
*****************************************************************
*/

void insert(); //Function declaration of Insert
void delete(); //Function declaration of Delete
void show(); //Function declaration of Show All
void show_letter(); //Function declaration of Show Corresponding
void read_file(char *name); //Function declaration of Read File
void save_file(char *name); //Function declaration of Save File
void read_binary(char *name); //Function declaration of Read Binary File
void save_binary(char *name); //Function declaration of Save Binary File

/*
*****************************************************************
*
*       main
*
*****************************************************************
*/

int main(int argc, char *argv[])
{

    int i;
    for (i = 0; i < SIZE; ++i)
    {
        lists[i] = NULL; //Creates the 26 empty linked lists
        listsTail[i] = NULL;
    }
    
    if (argc <= 2) //If a file name isn't given as an argument
    {
        printf("The names of the text file and/or binary files are missing.\n");
        return 0;
    }
    else
        read_file(argv[1]);

    int command;
    bool run = true;

    while(run)
    {
        printf("Options: 1. ADD PEOPLE\t2. DELETE PEOPLE\t3. SHOW ALL\t4. SHOW CORRESPONDING\t5. SAVE TO BINARY FILE\t6. READ BINARY FILE\t7. QUIT\nEnter Number: ");
        scanf("%d", &command); //User inputs 1-7

        switch (command)
        {
            case 1: //Insert
                insert();
                break;
            case 2: //Delete
                delete();
                break;
            case 3: //Show all the lists
                show();
                break;
            case 4: //Show the corresponding list
                show_letter();
                break;
            case 5: //Save to binary file
                save_binary(argv[2]);
                break;
            case 6: //Read from binary file
                read_binary(argv[2]);
                break;
            case 7: //Quit
                run = false;
                break;
            default: //If any number other than 1-7 is inputted
                printf("Not a valid option. Try again.\n");
                break;
        }
    }

    save_file(argv[1]);
    save_binary(argv[2]);
    
    free(lists[i-1]); //Deallocates the linked list
}

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