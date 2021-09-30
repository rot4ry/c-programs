#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void* hello(void* n)
{
    printf("PID[%ld]...jestem wątkiem #%ld! TID[%d]\n", (long)getpid(), (long)n, (int)pthread_self());
    pthread_exit(NULL);
}

int main(int argc, char **argv){
    pthread_t tid;
    int rc;
    long i, n;
    if(argc > 1)
    {
        sscanf(argv[1], "%ld", &n);
        for(i = 0; i < n; i++)
        {
            printf("Proces PID:[%ld] tworzy wątek...#%ld\n", (long)getpid(), (i+1));
            rc = pthread_create(&tid, NULL, hello, (void*)(i+1));
            if(rc!=0)
            {
                perror("!!! Error pthread_create() !!!");
                exit(rc);
            }
        }
    }
    else
    {
        printf("!!! Wywołanie powinno mieć postać: %s %s\n", argv[0], "<ilość_wątków>");
    }
    return 0;
}