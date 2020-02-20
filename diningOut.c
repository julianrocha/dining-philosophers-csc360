#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

// each philosopher is a thread

// each fork is a shared resource in the critical section

#define N 5

sem_t chopsticks[N];
pthread_t philosophers[N];
int philo_numbers[N];


void* philosophical_loop(void* philo_num){
    size_t* temp = philo_num;
    int num = *temp;

    int left = (num - 1) % N;
    if(left == -1){
	left = N - 1;
    }
    int right = num;
    int min = left < right ? left : right;
    int max = left < right ? right : left;

    while(1){
	printf("Philosoper %d is thinking...\n", num);    
        sleep(1);
	printf("Philosoper %d is hungry...\n", num);
	// Pickup lower ID chopstick
	sem_wait(&chopsticks[min]);
	printf("Philosoper %d picked up fork %d\n", num, min);
	// Pickup higher ID chopstick
	sem_wait(&chopsticks[max]);
	printf("Philosopher %d picked up fork %d\n", num, max);
	// Eat
        printf("Philosoper %d is eating...\n", num);
        sleep(1);
	// Putdown both forks
	sem_post(&chopsticks[min]);
	printf("Philosoper %d put down fork %d\n", num, min);
	sem_post(&chopsticks[max]);
	printf("Philosopher %d put down fork %d\n", num, max);
    }
}
  
  
int main() { 
    int i;
    // initialize chopsticks (semaphores)
    for(i = 0; i < N; i++){
        int n = sem_init(&(chopsticks[i]), 0, 1);
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
