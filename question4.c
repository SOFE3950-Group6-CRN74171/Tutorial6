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
#include <time.h>

#define BUFFER_SIZE 5
#define NUMBERS 10

int buffer[BUFFER_SIZE] = {0};
sem_t empty, full;

// Function to generate a random delay between 1 to 5 seconds
void random_delay() {
    int delay = rand() % 5 + 1;
    sleep(delay);
}

// Producer function
void *producer(void *arg) {
    int *numbers = (int *)arg;

    for (int i = 0; i < NUMBERS; ++i) {
        random_delay();

        sem_wait(&empty); // Wait if buffer is full

        // Find an empty slot in the buffer
        int j = 0;
        while (buffer[j] != 0) {
            j++;
        }

        // Produce item into buffer
        buffer[j] = numbers[i];
        printf("Produced %d\n", numbers[i]);

        sem_post(&full);  // Signal that buffer is no longer empty (allows consumer to consume)
    }

    pthread_exit(NULL);
}

// Consumer function
void *consumer() {
    for (int i = 0; i < NUMBERS; ++i) {
        random_delay();

        sem_wait(&full);  // Wait if buffer is empty

        // Find a non-empty slot in the buffer
        int j = 0;
        while (buffer[j] == 0) {
            j++;
        }

        // Consume item from buffer
        printf("Consumed %d\n", buffer[j]);
        buffer[j] = 0;

        sem_post(&empty); // Signal that buffer is no longer full
    }

    pthread_exit(NULL);
}

int main() {
    // Seeds the random number generator algorithm used by rand()
    srand(time(NULL));

    // Initialize semaphores
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, BUFFER_SIZE);

    // Prompt user for ten numbers
    int numbers[NUMBERS];
    printf("Enter ten numbers:\n");
    for (int i = 0; i < NUMBERS; ++i) {
        scanf("%d", &numbers[i]);
    }

    // Create producer and consumer threads
    pthread_t producer_thread, consumer_thread;
    pthread_create(&producer_thread, NULL, producer, (void *)numbers);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    // Wait for both threads to finish
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    // Print the contents of the buffer
    printf("Contents of buffer:\n");
    for (int i = 0; i < BUFFER_SIZE; ++i) {
        printf("%d ", buffer[i]);
    }
    printf("\n");

    // Destroy semaphores
    sem_destroy(&full);
    sem_destroy(&empty);

    return 0;
}
