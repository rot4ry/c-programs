#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
double* X;
double sum = 0.0;
unsigned long int n; //rozmiar tablicy
unsigned long int m; //ilość wątków

void* thread(unsigned long int id)
{
    double x = 0.0;
    for(unsigned long int i=id; i<n; i+=m)
    {
        x += *(X+i);
    }
    pthread_mutex_lock(&mutex);
    {
        sum += x;
    }
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

int main(int argc, char** argv)
{
    pthread_t* tid;
    unsigned long int i;
    if(argc > 2)
    {
        sscanf(argv[1], "%lu", &m);
        if(m < 2)
        { 
            printf("...m<2, przyjęto m=2...\n"); 
            m = 2;
        }
        tid = (pthread_t*)calloc((size_t)m, sizeof(pthread_t));
        sscanf(argv[2], "%lu", &n);
        if(n < 10)
        { 
            printf("...n<10,przyjęto n=1000...\n"); 
            n = 1000;
        }
        if(!(X = (double*)calloc((size_t)n, sizeof(double))))
        { 
            perror("Error calloc()"); 
            exit( 2 ); 
        }
        for(i=0; i<n; i++)
        { 
            *(X+i) = (double)(i+1); 
        }   
        for(i=0; i<m; i++)
        {
            if(pthread_create((tid+i), NULL, (void*(*)(void*))thread, (void*)i))
            { 
                free((void*)tid); 
                free((void*)X);
                perror( "Error pthread_create()"); 
                exit(2);
            }
        }
        for(i=0; i<m; i++)
        {
            if(pthread_join(*(tid+i), NULL))
            { 
                free((void*)tid); 
                free((void*)X);
                perror( "Error pthread_join()"); 
                exit(2);
            }
        }
        free((void*)tid); 
        free((void*)X);
        if(pthread_mutex_destroy(&mutex))
        { 
            perror("Error pthread_mutex_destroy()"); 
            exit(2);
        }
        printf("\nSuma elementów tablicy X wynosi %f\n", sum);
    }
    else
    { 
        printf("...wywołanie programu %s <ilość wątków> <rozmiar tablicy>\n", argv[0]); 
        exit(1); 
    }
    return 0;
}