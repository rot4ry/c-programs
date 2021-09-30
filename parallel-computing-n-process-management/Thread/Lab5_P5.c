#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

#define T 10 
#define N 100000

void* thread(void* n)
{
    double sum;
    printf("Wątek [#%ld] startuje...\n", (long)n);
    fflush(stdout);
    for(int i=0; i<N; i++)
    {
        sum += sin((double)i)*sin((double)i) + cos((double)i)*cos((double)i) - 1.0;
    }
    printf("Wątek [#%ld] zakończył działanie z suma = %e\n", (long)n, sum);
    fflush(stdout);
    pthread_exit(NULL);
}

int main()
{
    pthread_t threads[T];
    int rc;
    
    for(long t=0; t<T; t++)
    {
        rc = pthread_create(&threads[t], NULL, thread, (void*)(t+1));
        if(rc)
        { 
            perror("!!! Error pthread_create() !!!");
            exit(1);
        }
    }
    
    for(long t=0; t<T; t++)
    {
        rc = pthread_join(threads[t], NULL);
        if(rc)
        {
            perror("!!! Error pthread_join() !!!");
            exit(2);
        }
    }
    pthread_exit(NULL);
}
