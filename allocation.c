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
#include <limits.h>

typedef struct Process
{
    char* name;
    long startLocation;
    long size;
    struct Process* prevProcess;
    struct Process* nextProcess;
}Process;

//global variables
Process* firstProcess = NULL;
long totalMemory;

//function headers
void requestMemory(char* name, long size, char type);
void releaseMemory(char* name);
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
            split_string = strtok(NULL, " \n");
            char* name = (char *) malloc(strlen(split_string));
            strcpy(name, split_string);

            releaseMemory(name);
            free(name);
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
    if (firstProcess == NULL) {
        *process = NULL;
        return 1;
    }
    
    Process* bestPrevProcess = NULL;
    long bestHoleSize = firstProcess->startLocation;
    if (bestHoleSize < size) {
        bestHoleSize = LONG_MAX;
    }
    
    long holeStart = firstProcess->startLocation + firstProcess->size;
    long holeEnd;
    
    Process* curr = firstProcess;
    long currSize;
    while (curr != NULL) {
        if (curr->nextProcess != NULL) {
            holeEnd = curr->nextProcess->startLocation;
        } else {
            holeEnd = totalMemory;
        }
        
        currSize = holeEnd - holeStart;
        if (currSize >= size && currSize < bestHoleSize) {
            bestPrevProcess = curr;
            bestHoleSize = currSize;
        }
        
        curr = curr->nextProcess;
        if (curr != NULL) {
            holeStart = curr->startLocation + curr->size;
        }
    }
    
    if (bestHoleSize != LONG_MAX) {
        *process = bestPrevProcess;
        return 1;
    } else {
        // Failed to find enough memory
        return 0;
    }
}

//worst fit
int worstFit(long size, Process** process) {
    if (firstProcess == NULL) {
        *process = NULL;
        return 1;
    }
    
    Process* bestPrevProcess = NULL;
    long bestHoleSize = firstProcess->startLocation;
    if (bestHoleSize < size) {
        bestHoleSize = LONG_MIN;
    }
    
    long holeStart = firstProcess->startLocation + firstProcess->size;
    long holeEnd;
    
    Process* curr = firstProcess;
    long currSize;
    while (curr != NULL) {
        if (curr->nextProcess != NULL) {
            holeEnd = curr->nextProcess->startLocation;
        } else {
            holeEnd = totalMemory;
        }
        
        currSize = holeEnd - holeStart;
        if (currSize >= size && currSize > bestHoleSize) {
            bestPrevProcess = curr;
            bestHoleSize = currSize;
        }
        
        curr = curr->nextProcess;
        if (curr != NULL) {
            holeStart = curr->startLocation + curr->size;
        }
    }
    
    if (bestHoleSize != LONG_MIN) {
        *process = bestPrevProcess;
        return 1;
    } else {
        // Failed to find enough memory
        return 0;
    }
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
        printf("No hole of sufficient size\n");
        return;
    }

    newProcess->size = size;
    newProcess->name = name;
    if (curr == NULL) { //add new process to the beginning
        newProcess->nextProcess = firstProcess;
        newProcess->prevProcess = NULL;

        if (firstProcess != NULL) {
            firstProcess->prevProcess = newProcess;
        }
        
        firstProcess = newProcess;  //update new first process
        newProcess->startLocation = 0;
    }
    else { //add to middle/end
        newProcess->nextProcess = curr->nextProcess;            //update next process for new, including NULL
        newProcess->prevProcess = curr;                         //update prev process for new
        if (newProcess->nextProcess != NULL) { 
            newProcess->nextProcess->prevProcess = newProcess;      //update prev process for next process
        }

        curr->nextProcess = newProcess;                         //update next process for prev process

        newProcess->startLocation = curr->startLocation + curr->size;

    }

    printf("Successfully allocated %ld to process %s\n", size, name);
}

//RL
void releaseMemory(char* name) {
    Process* curr = firstProcess;

    while (curr != NULL && strcmp(curr->name, name)) {
        curr = curr->nextProcess;
    }

    if (curr != NULL) {
        printf("Releasing memory for process %s\n", name);

        if (curr->nextProcess != NULL) {
            curr->nextProcess->prevProcess = curr->prevProcess;
        }

        if (curr == firstProcess) {
            firstProcess = curr->nextProcess;
        } 
        else {
            curr->prevProcess->nextProcess = curr->nextProcess;
        }

        free(curr);
        printf("Successfully released memory for process %s\n", name);
    }

    else {
        printf("There is no process with this name\n");
    }
}

//C
void compactMemory() {
    Process* curr = firstProcess;
    long startLocation = 0;
    while (curr != NULL) {
        if (curr->startLocation > startLocation) {
            curr->startLocation = startLocation;
        }
        
        startLocation = curr->startLocation + curr->size;
        curr = curr->nextProcess;
    }
    printf("Compaction process is successful\n");
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
            holeEnd = totalMemory - 1;
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
