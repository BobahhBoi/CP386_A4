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

//global variables
Process* firstProcess;
int totalMemory;

//function headers
void requestMemory(char* name, int size, char type);
void releaseMemory();
void compactMemory();
void status();


int main(int argc, char *argv[])
{
    char user_command[20];
    char* split_string;

    totalMemory = atoi(argv[1]);

    //loop
    while (true) {
        printf("allocator>");
        fgets (user_command, 20, stdin);

        split_string = strtok(user_command, " \n");

        if (!strcmp(split_string,"RQ")){
            char* name;
            int size; 
            char type;
            
            split_string = strtok(NULL, " \n");
            //printf("%s\n",split_string);
            name = split_string;

            split_string = strtok(NULL, " \n");
            //printf("%s\n",split_string);
            size = atoi(split_string);

            split_string = strtok(NULL, " \n");
            //printf("%s\n",split_string);
            type = split_string[0];
            

            requestMemory(name, size, type);
        }

        else if (!strcmp(split_string,"RL")){
            releaseMemory();
        }

        else if (!strcmp(split_string,"C")){
            compactMemory();
        }

        else if (!strcmp(split_string,"Status")){
            status();
        }

        else if (!strcmp(split_string,"Exit")){
            break;
        }
    }
    
    return 0;
}

void firstFit() {

}

void bestFit() {
    
}

void worstFit() {
    
}


void requestMemory(char* name, int size, char type) {
    printf("%s, %d, %c\n", name, size, type);

    Process* newProcess = (Process*)malloc(sizeof(Process));

}
void releaseMemory() {

}
void compactMemory() {

}
void status() {

}
