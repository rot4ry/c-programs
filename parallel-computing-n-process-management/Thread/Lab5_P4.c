#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void* thread(void* arg)
{
    printf("W wątku...\n"); 
    fflush(stdout);
    for(int i=0; i<5; i++)
    { 
        printf("\t%3d s\n", (i+1)); 
        fflush(stdout); 
        sleep(1); 
    }
    printf("Koniec, zwracam sterowanie\n"); 
    fflush(stdout);
    pthread_exit(NULL);
}

int main()
{
    pthread_t tid;
    int rc = pthread_create(&tid, NULL, thread, NULL);
    if(rc)
    {
        perror("!!! Error pthread_create() !!!");
        exit(1); 
    }
    else
    {
        if(pthread_join(tid, NULL))
        { 
            perror("!!! Error pthread_join() !!!");
            exit(2);
        }
    }
    return 0;
}