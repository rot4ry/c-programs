#include <stdio.h>
#include <time.h>  
#include <pthread.h>

int COUNTER;
#define R 4
#define W 2 
#define N 5

pthread_mutex_t writer_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t reader_mutex = PTHREAD_MUTEX_INITIALIZER;

void* writer(void* arg)
{
    for(int n = 0; n < N; n++)
    {
        pthread_mutex_lock(&writer_mutex);
        printf("[%lu] writer -> START\n", (unsigned long)pthread_self());
        sleep(1);
        printf("[%lu] writer -> STOP\n", (unsigned long)pthread_self());
        pthread_mutex_unlock(&writer_mutex);
        sleep(n);
    }
    pthread_exit(NULL);
}

void* reader(void* arg)
{
    int n = 0;
    while(1)
    {
        pthread_mutex_lock(&reader_mutex);
        COUNTER++;
        if(COUNTER == 1)
        { 
            pthread_mutex_lock(&writer_mutex); 
        }
        pthread_mutex_unlock(&reader_mutex);
        printf("[%lu] reader -> START\n", (unsigned long)pthread_self());
        sleep(1);
        printf("[%lu] reader -> STOP\n", (unsigned long)pthread_self());
        pthread_mutex_lock(&reader_mutex);
        COUNTER--;
        if(!COUNTER)
        { 
            pthread_mutex_unlock(&writer_mutex); 
        }
        pthread_mutex_unlock(&reader_mutex);
        sleep(n); 
        n++;
    }
    pthread_exit(NULL);
}

int main()
{
    pthread_t readers[R];
    pthread_t writers[W];
    COUNTER = 0;
    
    for(int t = 0; t < R; t++)
    { 
        pthread_create((readers + t), NULL, reader, NULL); 
    }
    
    for(int t = 0; t < W; t++)
    { 
        pthread_create((writers + t), NULL, writer, NULL); 
    }
    for(int t = 0; t < W; t++)
    {
        pthread_join(*(writers + t), NULL); 
    }
    return 0;
}