#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>
#include <semaphore.h>

#define FOOD 50
#define N 5
#define LEFT (id + N - 1) % N
#define RIGHT (id + 1) % N
#define THINKING 0
#define HUNGRY 1
#define EATING 2
#define TRUE 1

typedef sem_t semaphore;
int state[N];
semaphore mutex;
semaphore s[N];

void *philosopher(void *id);
void eat(int id);
void take_forks(int id);
void put_forks(int id);
void test(int id);
void up(semaphore *sem);
void down(semaphore *sem);
int food_on_table();

int main() {
    pthread_t philosophers[N];
    int i;

    // Initialize semaphores
    sem_init(&mutex, 0, 1);
    for (i = 0; i < N; i++) {
        sem_init(&s[i], 0, 0);
        pthread_create(&philosophers[i], NULL, philosopher, (void *)i);
        state[i] = THINKING;
    }

    // Wait for the philosophers to finish
    for (i = 0; i < N; i++) {
        pthread_join(philosophers[i], NULL);
    }

    return 0;
}

void *philosopher(void *num) {
    int id = (int)num;

    while (food_on_table()) {
        printf("Philosopher %d is done thinking and now ready to eat.\n", id);
        take_forks(id);
        eat(id);
        printf("Philosopher %d finished eating.\n", id);
        put_forks(id);
    }
}

void eat(int id) {
    printf("Philosopher %d is eating.\n", id);
}

void take_forks(int id) {
    down(&mutex);
    state[id] = HUNGRY;
    test(id);
    up(&mutex);
    down(&s[id]);
}

void put_forks(int id) {
    down(&mutex);
    state[id] = THINKING;
    test(LEFT);
    test(RIGHT);
    up(&mutex);
}

void test(int id) {
    if (state[id] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING) {
        printf("Philosopher %d: got %s chopstick %d\n", id, "RIGHT", RIGHT);
        printf("Philosopher %d: got %s chopstick %d\n", id, "LEFT", LEFT);
        state[id] = EATING;
        up(&s[id]);
    }
}

void up(semaphore *sem) {
    sem_post(sem);
}

void down(semaphore *sem) {
    sem_wait(sem);
}

int food_on_table() {
    static int food = FOOD;
    int myfood;

    down(&mutex);

    if (food > 0) {
        food--;
    }
    myfood = food;

    up(&mutex);
    return myfood;
}
