#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <limits.h>

void* task(void* arg)
{
    double x;
    x = 1.0 + 1.0;
    return NULL;
}

int main(int argc, char **argv)
{
    unsigned long n;
    pthread_t tid;
    
    if(argc > 1)
    {
        if(sscanf(argv[1], "%lu", &n) == 1)
        {
            for(unsigned long i=0; i<n; i++)
            {
                if(pthread_create(&tid, NULL, task, NULL))
                { 
                    perror( "!!! Error pthread_create() !!!");
                    exit(1);
                }
                else
                { 
                    pthread_join(tid, NULL);
                }
            }
        }
        else
        {
            printf("!!! Błędny argument [%s] wywołania [%s]\n", argv[1], argv[0]);
        }
    }
    else
    {
        printf("!!! %s [ilość < ULONG_MAX=%lu] !!!\n", argv[0], ULONG_MAX);
    }
    return 0;
}