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

int main(void)
{
    pid_t pid;

    // Fork a child process
    pid = fork();
    // Error case for failing fork
    if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        sleep(1);
        printf("Child process\n");
        exit(EXIT_SUCCESS);
    } else {
        // Parent process
        int status;
        wait(&status); // Wait for the child process to terminate

        if (WIFEXITED(status)) {
            printf("Child process exited with status: %d\n", WEXITSTATUS(status));
        } else {
            printf("Child process terminated abnormally\n");
        }

        printf("Parent Process\n");
    }

    return 0;
}
