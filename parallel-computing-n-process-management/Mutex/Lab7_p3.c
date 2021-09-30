#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int N = 0;
void* thread(int id)
{
    pthread_mutex_lock(&mutex);
    {
        N += id;
    }
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}
int main(int argc, char** argv)
{
    pthread_t* tid;
    int n;
    if(argc > 1)
    {
        sscanf(argv[1], "%d", &n);
        if(n < 2)
        { 
            printf("..n<2, przyjęto n = 2...\n");
            n = 2;
        }
        if(!(tid = (pthread_t*)calloc((size_t)n, sizeof(pthread_t))))
        {   
            perror("Error calloc()"); 
            exit(2); 
        }
        for(int i=0; i<n; i++)
        {
            if(pthread_create((tid+i), NULL, (void*(*)(void*))thread, (void*)(i+1)))
            {
                free((void*)tid);
                perror("Error pthread_create()");
                exit(2);
            }
        }
        for(int i=0; i<n; i++)
        {
            if(pthread_join(*(tid+i), NULL))
            {
                free((void*)tid);
                perror("Error pthread_join()");
                exit(2);
            }
        }
        free((void*)tid);
        if(pthread_mutex_destroy(&mutex))
        { 
            perror("Error pthread_mutex_destroy()"); 
            exit(2); 
        }
        printf("Suma ciągu n = %d liczb naturalnych wynosi n*(n+1)/2 = %d\n", n, N);
    }
    else
    { 
        printf("\nWywołanie programu %s <ilość wątków>\n", argv[0]); 
        exit(1);
    }
    return 0;
}