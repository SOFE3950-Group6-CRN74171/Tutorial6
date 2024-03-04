/*
 * Tutorial 6 POSIX Thread Part II Project for SOFE 3950U : Operating Systems
 *
 * Copyright (C) 2024, <Mostafa Abedi, Nathaniel Manoj, Calvin Reveredo>
 * All rights reserved.
 *
*/
#define _XOPEN_SOURCE 700 // required for barriers to work
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
/*
Parent Process
|--- Child Process 1
|    |--- Sleeps for 1 sec
|    |--- Prints "Child Process"
|-Waits for child
|-Prints "Parent Process"
*/
int main() {
    pid_t pid;

    pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork failed\n");
        return 1;
    } else if (pid == 0) {
        // Child process
        sleep(1);
        printf("Child process\n");
        exit(0); // Child process exits normally
    } else {
        // Parent process
        int status;
        wait(&status); // Parent waits for the child to terminate
        if (!WIFEXITED(status)) { //Error Case
            printf("Child process terminated abnormally\n");
        }
        printf("Parent process\n");
    }

    return 0;
}
