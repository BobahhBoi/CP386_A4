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

Process* firstFit(int size) {
    long startPoint = 0;
    Process* curr = firstProcess;
    while (curr != NULL) {
        if (curr->startLocation - startPoint >= size) {
            break;
        }
        
        startPoint = curr->startLocation + curr->size;
        curr = curr->nextProcess;
    }
    
    return curr;
}

Process* bestFit(int size) {
    
}

Process* worstFit(int size) {
    
}


void requestMemory(char* name, int size, char type) {
    printf("%s, %d, %c\n", name, size, type);

    Process* curr;
    Process* newProcess = (Process*)malloc(sizeof(Process));

    switch(type){
    case 'F':
        curr = firstFit(size);
        break;
    case 'B':
        curr = bestFit(size);
        break;
    case 'W':
        curr = worstFit(size);
        break;

    }

    newProcess->size = size;
    newProcess->name = name;
    if (curr == NULL) {
        newProcess->nextProcess = firstProcess;
        firstProcess = newProcess;
        newProcess->startLocation = 0;
    }
    else {
        newProcess->nextProcess = curr->nextProcess;
        curr->nextProcess = newProcess;

        newProcess->startLocation = curr->startLocation + curr->size;

    }
}

void releaseMemory() {

}
void compactMemory() {

}
void status() {

}