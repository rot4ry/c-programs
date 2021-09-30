#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define N 5
#define CYCLE 1
pthread_mutex_t sticks[N];
pthread_mutex_t eat;

void* dinner( void* arg )
{
    int v;
    int eating = 0;
    v = *((int*)arg) + 1;
    while(eating < CYCLE)
    {
        printf("[%d]Thinking...\n", v); 
        sleep(v/2);
        printf("[%d]Hungry...\n", v);
        pthread_mutex_lock(&eat);
        pthread_mutex_lock((sticks + v));
        pthread_mutex_lock((sticks + (v + 1)%N));
        pthread_mutex_unlock(&eat);
        printf("[%d]Dinner start...\n", v);
        eating++; 
        sleep(1);
        printf("[%d]Dinner stop...\n", v);
        pthread_mutex_unlock((sticks + v));
        pthread_mutex_unlock((sticks + (v + 1)%N));
    }
    pthread_exit(NULL);
}

int main()
{
    pthread_t tid[N];
    int n[N];
    pthread_mutex_init(&eat, NULL);
    for(int i=0; i<N; i++)
    { 
        pthread_mutex_init((sticks+i), NULL); 
    }

    for(int i=0; i<N; i++)
    { 
        *(n+i) = i; 
        pthread_create((tid+i), NULL, dinner, (void*)(n+i)); 
    }

    for(int i=0; i<N; i++)
    { 
        pthread_join(tid[i], NULL); 
    }

    pthread_exit(0);
}