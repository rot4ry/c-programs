#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int __GO = 0;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* producer(void* arg)
{
    printf("[%lu] producent: ???\n", (unsigned long)pthread_self());
    sleep(1);
    pthread_mutex_lock(&mutex);
    __GO = 1;
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

void* consumer(void* arg)
{
    printf("[%lu] konsument: czeka...\n", (unsigned long)pthread_self());
    pthread_mutex_lock(&mutex);
    while(!__GO)
    { 
        pthread_cond_wait(&cond, &mutex); 
    }
    pthread_mutex_unlock(&mutex);
    printf("[%lu] konsument: kontynuacja\n", (unsigned long)pthread_self());
    pthread_exit(NULL);
}

int main(int argc, char** argv)
{
    pthread_t consumer_id, producer_id;
    if(pthread_create(&consumer_id, NULL, consumer, NULL))
    { 
        perror("Error pthread_create() - consumer"); 
        exit(1);
    }
    if(pthread_create(&producer_id, NULL, producer, NULL))
    { 
        perror("Error pthread_create() - producer"); 
        exit(1);
    }
    if(pthread_join(consumer_id, NULL))
    { 
        perror("Error pthread_join() - consumer"); 
        exit(1);
    }
    if(pthread_join( producer_id, NULL))
    { 
        perror("Error pthread_join() - producer"); 
        exit(1);
    }
    return 0;
}