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
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/wait.h>

#define NUM_THREADS 5

// Global variable for total sum
int total_sum = 0;

// Semaphore for mutual exclusion
sem_t semaphore;

// Function to calculate factorial
int factorial(int n) {
    if (n == 0 || n == 1) {
        return 1;
    }
    return n * factorial(n - 1);
}

// Thread function
void *factorial_thread(void *arg) {
    int *num = (int *)arg;

    // Calculate factorial
    int fac = factorial(*num);

    // Wait until previous total_sum value is available
    sem_wait(&semaphore);
    total_sum += fac;
    printf("Factorial of %d: %d\n", *num, fac);
    printf("Total sum: %d\n", total_sum);
    sem_post(&semaphore);

    pthread_exit(NULL);
}

int main(void)
{
    FILE *numbers_file, *sum_file;
    pid_t pid;
    pthread_t threads[NUM_THREADS];
    int numbers[NUM_THREADS];

    // Initialize semaphore
    sem_init(&semaphore, 0, 1);

    // Open file for writing numbers
    numbers_file = fopen("numbers.txt", "w");
    if (numbers_file == NULL) {
        perror("Error opening numbers.txt");
        exit(EXIT_FAILURE);
    }

    // Prompt user for five numbers and write to file
    printf("Enter five numbers:\n");
    for (int i = 0; i < NUM_THREADS; ++i) {
        scanf("%d", &numbers[i]);
        fprintf(numbers_file, "%d\n", numbers[i]);
    }
    fclose(numbers_file);
    
    // Fork process
    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        numbers_file = fopen("numbers.txt", "r");
        if (numbers_file == NULL) {
            perror("Error opening numbers.txt");
            exit(EXIT_FAILURE);
        }

        // Read numbers from file and create threads
        for (int i = 0; i < NUM_THREADS; ++i) {
            fscanf(numbers_file, "%d", &numbers[i]);
            pthread_create(&threads[i], NULL, factorial_thread, &numbers[i]);
        }
        fclose(numbers_file);

        // Wait for all threads to finish
        for (int i = 0; i < NUM_THREADS; ++i) {
            pthread_join(threads[i], NULL);
        }

        // Write total sum to file
        sum_file = fopen("sum.txt", "w");
        if (sum_file == NULL) {
            perror("Error opening sum.txt");
            exit(EXIT_FAILURE);
        }
        fprintf(sum_file, "%d\n", total_sum);
        fclose(sum_file);

        exit(EXIT_SUCCESS);
    } else {
        // Parent process
        int status;
        wait(&status); // Wait for child process to terminate

        // Read total sum from file
        sum_file = fopen("sum.txt", "r");
        if (sum_file == NULL) {
            perror("Error opening sum.txt");
            exit(EXIT_FAILURE);
        }
        fscanf(sum_file, "%d", &total_sum);
        fclose(sum_file);

        // Print total sum
        printf("Total sum: %d\n", total_sum);

        // Destroy semaphore
        sem_destroy(&semaphore);
    }

    return 0;
}
