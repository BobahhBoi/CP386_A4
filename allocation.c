/*
------------------------------------------------------------------------------------------
File:    allocation.c
Purpose: Assignment 4, Question 1
------------------------------------------------------------------------------------------
Author:  Alex Lau (GitHub: BobahhBoi) , Tatiana Olenciuc (GitHub: tygragamand)
Repository: https://github.com/BobahhBoi/CP386_A4
Version  2022-07-22
------------------------------------------------------------------------------------------
*/

//Includes
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

typedef struct Process
{
    char* name;
    long startLocation;
    long size;
    struct Process* nextProcess;
    struct Process* prevProcess;
}Process;

Process* firstProcess;
int totalMemory;

int main(int argc, char *argv[])
{
    char user_command[20];
    char* split_string;

    totalMemory = atoi(argv[1]);

    //loop
    while (true) {
        
        printf("allocator>");
        scanf("%s", user_command);

        split_string = strtok(user_command, " \n");

        if (!strcmp(split_string,"RQ")){
            
        }

        else if (!strcmp(split_string,"RL")){
            
        }

        else if (!strcmp(split_string,"C")){
            
        }

        else if (!strcmp(split_string,"Status")){
            
        }

        else if (!strcmp(split_string,"Exit")){
            break;
        }
    }

    //first fit


    //best fit


    //worst fit
    
    return 0;
}
