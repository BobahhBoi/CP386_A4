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
    struct Process* prevProcess;
    struct Process* nextProcess;
}Process;

//global variables
Process* firstProcess;
long totalMemory;

//function headers
void requestMemory(char* name, long size, char type);
void releaseMemory();
void compactMemory();
void status();


int main(int argc, char *argv[])
{
    setbuf(stdout, NULL);

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
            long size; 
            char type;
            
            split_string = strtok(NULL, " \n");
            //printf("%s\n",split_string);
            name = (char *) malloc(strlen(split_string));
            strcpy(name, split_string);

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

//first fit
int firstFit(long size, Process** process) {
    //printf("FIRST FIT");
    if (firstProcess == NULL || firstProcess->startLocation >= size) {
        *process = NULL;
        return 1;
    }
    
    long holeStart = firstProcess->startLocation + firstProcess->size;
    long holeEnd;
    
    Process* curr = firstProcess;
    while (curr != NULL) {
        if (curr->nextProcess != NULL) {
            holeEnd = firstProcess->nextProcess->startLocation;
        } else {
            holeEnd = totalMemory;
        }
        
        if (holeEnd - holeStart > size) {
            *process = curr;
            return 1;
        }
        
        holeStart = curr->startLocation + curr->size;
        curr = curr->nextProcess;
    }
    
    // Failed to find enough memory
    return 0;
}

//best fit
int bestFit(long size, Process** process) {
    
}

//worst fit
int worstFit(long size, Process** process) {
    
}


//RQ
void requestMemory(char* name, long size, char type) {
    //printf("%s, %d, %c\n", name, size, type);

    int success = 0;
    Process* curr;
    Process* newProcess = (Process*)malloc(sizeof(Process));

    switch(type){
    case 'F':
        success = firstFit(size, &curr);
        break;
    case 'B':
        success = bestFit(size, &curr);
        break;
    case 'W':
        success = worstFit(size, &curr);
        break;
    }
    
    if (!success) {
        printf("No hole of sufficient size");
        return;
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

//RL
void releaseMemory(char* name) {
    
}

//C
void compactMemory() {

}

//Status
void status() {
    long allocatedMemory = 0;
    long freeMemory;
    long endLocation;

    //calculate allocated memory
    Process* curr = firstProcess;

    while (curr != NULL) {
        allocatedMemory += curr->size;
        curr = curr->nextProcess;
    }
    printf("Partitions [Allocated memory = %ld]:\n", allocatedMemory);

    //print each allocated partition
    curr = firstProcess;
    while (curr != NULL) {
        endLocation = curr->startLocation + curr->size - 1;
        printf("Address [%ld:%ld] Process %s\n", curr->startLocation, endLocation, curr->name);

        curr = curr->nextProcess;
    }
    printf("\n");

    //calculate free memory
    freeMemory = totalMemory - allocatedMemory;
    printf("Holes [Free memory = %ld]\n", freeMemory);

    //print each hole
    long holeStart = 0;
    long holeEnd;
    long holeLen;
    curr = firstProcess;

    while (holeStart <= totalMemory) {
        if (curr == NULL) {  //reached the end but still memory left
            holeEnd = totalMemory;
        }
        else {  //curr exists
            holeEnd = curr->startLocation - 1;
        }
        
        holeLen = holeEnd - holeStart + 1;
        if (holeEnd >= holeStart) {
            printf("Address [%ld:%ld] len = %ld\n", holeStart, holeEnd, holeLen);
        }

        if (curr == NULL) {
            break;
        }

        holeStart = curr->startLocation + curr->size;   
        curr = curr->nextProcess; 
          
    }
}