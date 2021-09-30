#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
int N=0;
void* thread(void* arg)
{
    int n;
    for(int i=0; i<5; i++)
    {
        n = N;
        n++;
        printf("thread() [%lu]\n",(unsigned long)pthread_self());
        fflush(stdout);
        sleep(1);
        N = n;
    }
    pthread_exit(NULL);
}
int main()
{
    pthread_t tid;
    if(pthread_create(&tid, NULL, thread, NULL))
    { 
        perror("!!! Error pthread_create() !!!"); 
        exit(1);
    }
    for(int i=0; i<5; i++)
    {
        N--;
        printf("main()\t[%lu]\n", (unsigned long)pthread_self());
        fflush(stdout);
        sleep(1);
    }
    if(pthread_join(tid, NULL))
    { 
        perror("!!! Error pthread_join() !!!"); 
        exit(2);
    }
    printf("\nglobalnie N=%d, po wykonaniu 5+5 iteracji\n", N);
    return 0;
}