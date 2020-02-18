#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

// each philosopher is a thread

// each fork is a shared resource in the critical section

#define N 5
#define CLEAN 1
#define DIRTY 0

typedef struct chopstick {
    int state;
    sem_t held;
} chopstick;

chopstick chopsticks[N];
pthread_t philosophers[N];
int philo_numbers[N];


void* philosophical_loop(void* philo_num){
    size_t* temp = philo_num;
    int num = *temp;

    if(num < N - 1){
        sem_wait(&chopsticks[num + 1].held);
    }
    if(num == 0){
        sem_wait(&chopsticks[N - 1].held);
    }

    sleep(4);

    if(num > 0){
        sem_wait(&chopsticks[num - 1].held);
    }

    while(1){
        printf("Philosoper %d is thinking...\n", num);
        sleep(1);
        printf("Philosoper %d is hungry...\n", num);
        printf("Philosoper %d is eating...\n", num);
        sleep(1);
    }
}
  
  
int main() { 
    int i;

    // initialize chopsticks (semaphores)
    for(i = 0; i < N; i++){
        chopsticks[i].state = CLEAN;
        int n = sem_init(&(chopsticks[i].held), 0, 1);
        if (n != 0) puts("sem_init failed");
    }

    // initialize philosopher numbers (global thread function parameters)
    for(i = 0; i < N; i++){
        philo_numbers[i] = i;
    }

    // initialize philosophers (create and start threads)
    for(i = 0; i < N; i++){
        pthread_create(&philosophers[i], NULL, philosophical_loop, &philo_numbers[i]);
    }

    // wait for philosophers to finish (join the threads back to main)
    for(i = 0; i < N; i++){
        pthread_join(philosophers[i], NULL);
    }

    return 0; 
}
