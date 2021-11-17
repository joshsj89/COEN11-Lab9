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
#include "lab9.h"

#define NODE struct contact
#define SIZE 26

NODE *lists[SIZE]; //Array of linked lists
NODE *listsTail[SIZE]; //Array of linked lists' tails
char *fileHeader = "Names\tNumbers\t\n\n----------------------------------\n\n"; //Header of the text file

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
        scanf("%d", &command); //User inputs 1-8

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
            case 8:
                for (i = 0; i < SIZE; ++i)
                {
                    reverse(lists[25 - i], (25 - i));
                    NODE *t = lists[25 - i];
                    while (t != NULL) //While node is not null
                    {
                        printf("%s\t%s\n", t->name, t->number); //Prints the name and number of one node
                        t = t->next; //Contiues to the next node
                    }
                    reverse(lists[25 - i], (25 - i));
                }
                break;
            default: //If any number other than 1-8 is inputted
                printf("Not a valid option. Try again.\n");
                break;
        }
    }

    save_file(argv[1]);
    save_binary(argv[2]);
    
    free(lists[i-1]); //Deallocates the linked list
}