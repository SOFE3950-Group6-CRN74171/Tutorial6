/*
 * Tutorial 6 POSIX Thread Part II Project for SOFE 3950U : Operating Systems
 *
 * Copyright (C) 2024, <Mostafa Abedi, Nathaniel Manoj, Calvin Reveredo>
 * All rights reserved.
 *
*/
#define _XOPEN_SOURCE 700 // required for barriers to work
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
/*
Master Process
|--- Child Process 1
|    |--- Reads child1.txt
|    |--- Prints content of child1.txt
|
|--- Child Process 2
     |--- Reads child2.txt
     |--- Prints content of child2.txt
*/
int main(void) {
    // Create two child processes
    pid_t pid1, pid2;
    pid1 = fork();
    // Error case for failing fork
    if (pid1 < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else if (pid1 == 0) { // Child 1 process
        // Wait for 1 second
        sleep(1);
        // Read and print content of child1.txt
        FILE *file = fopen("child1.txt", "r");
        if (file == NULL) {
            perror("Error opening file");
            exit(EXIT_FAILURE);
        }
        char line[100];
        fgets(line, sizeof(line), file);
        printf("Child 1: %s", line);
        fclose(file);
        exit(EXIT_SUCCESS);
    } else { // Master process
        pid2 = fork();
        if (pid2 < 0) {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        } else if (pid2 == 0) { // Child 2 process
            // Wait for 1 second
            sleep(1);
            // Read and print content of child2.txt
            FILE *file = fopen("child2.txt", "r");
            if (file == NULL) {
                perror("Error opening file");
                exit(EXIT_FAILURE);
            }
            char line[100];
            fgets(line, sizeof(line), file);
            printf("Child 2: %s", line);
            fclose(file);
            exit(EXIT_SUCCESS);
        } else { // Master process
            // Write contents to child1.txt
            FILE *file1 = fopen("child1.txt", "w");
            if (file1 == NULL) {
                perror("Error opening file");
                exit(EXIT_FAILURE);
            }
            fprintf(file1, "child 1\n");
            fclose(file1);
            // Write contents to child2.txt
            FILE *file2 = fopen("child2.txt", "w");
            if (file2 == NULL) {
                perror("Error opening file");
                exit(EXIT_FAILURE);
            }
            fprintf(file2, "child 2\n");
            fclose(file2);
            // Wait for both child processes to finish
            wait(NULL);
            wait(NULL);
            printf("Master process finished.\n");
        }
    }
    return 0;
}
