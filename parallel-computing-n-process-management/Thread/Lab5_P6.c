#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
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
    int status;
    pid_t pid;
    if(argc > 1)
    {
        if(sscanf(argv[1], "%lu", &n) == 1)
        {
            for(unsigned long i=0; i<n; i++)
            {
                switch((int)(pid = fork()))
                {
                    case -1:
                        perror( "!!! Error fork() !!!");
                        exit(1);
                        break;

                    case 0: 
                        task(NULL); 
                        exit(0); 
                        break;

                    default: 
                        waitpid(pid, &status, 0);
                }
            }
        }
        else
        { 
            printf("!!! Błędny argument [%s] wywołania [%s] !!!\n", argv[1], argv[0]);
        }
    }
    else
    { 
        printf("!!! %s [ilość < ULONG_MAX = %lu] !!!\n", argv[0], ULONG_MAX);
    }
    return 0;
}