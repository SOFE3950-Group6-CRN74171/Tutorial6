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

#define LENGTH 5

// Global array to store moving sum
int moving_sum[LENGTH] = {0};

// Semaphore for mutual exclusion
sem_t semaphore;

// Struct to hold number and index
struct Nums {
    int number;
    int index;
};

// Function to calculate factorial
int factorial(int n) {
    if (n == 0 || n == 1) {
        return 1;
    }
    return n * factorial(n - 1);
}

// Thread function
void *factorial_thread(void *arg) {
    struct Nums *nums = (struct Nums *)arg;

    // Calculate factorial
    int fac = factorial(nums->number);

    // Wait until previous moving_sum value is available
    if (nums->index > 0) {
        while (1) {
            sem_wait(&semaphore);
            if (moving_sum[nums->index - 1] > 0) {
                fac += moving_sum[nums->index - 1];
                break;
            }
        }
    }

    // Add to moving_sum
    moving_sum[nums->index] = fac;

    // Signal completion
    sem_post(&semaphore);

    pthread_exit(NULL);
}

int main(void)
{
    // Initialize semaphore
    sem_init(&semaphore, 0, 1);

    // Array to hold thread IDs
    pthread_t threads[LENGTH];

    // Array to hold thread arguments
    struct Nums args[LENGTH];

    // Prompt for input numbers
    printf("Enter five numbers:\n");
    for (int i = 0; i < LENGTH; i++) {
        scanf("%d", &args[i].number);
        args[i].index = i;

        // Create thread
        if (pthread_create(&threads[i], NULL, factorial_thread, (void *)&args[i]) != 0) {
            perror("Error creating thread");
            exit(EXIT_FAILURE);
        }
    }

    // Wait for all threads to finish
    for (int i = 0; i < LENGTH; i++) {
        pthread_join(threads[i], NULL);
    }

    // Print moving_sum
    printf("Moving sum:\n");
    for (int i = 0; i < LENGTH; i++) {
        printf("%d ", moving_sum[i]);
    }
    printf("\n");

    // Destroy semaphore
    sem_destroy(&semaphore);

    return 0;
}
