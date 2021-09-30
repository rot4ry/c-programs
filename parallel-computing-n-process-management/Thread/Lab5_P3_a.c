#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#define N 10000 

void* thread(void* array){
    double sum, avg;
    for(int i=0; i<N; i++)
    {
        sum += *((double*)array+i);
    }
    avg = sum/N;
    printf("AVG = %16.10f\n", avg);
    return ((void*)0);
}

int main()
{
    pthread_t tid;
    double x[N];
    for(int i=0; i<N; i++)
    {
        *(x+i) = ((double)rand())/(RAND_MAX); 
    }
    printf("Wysyłam dane do wątku TID:[%d]\n", (int)tid);
    pthread_create(&tid, NULL, thread, (void*)x);
    printf("...Czekam na wątek\n");
    return 0;
}