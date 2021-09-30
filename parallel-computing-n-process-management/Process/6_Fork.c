#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main(){
    int status;

    switch( fork() )
    { 
        case -1: 
            printf("-1 Error\n");
            break;

        case 0: 
            printf("<child> pozdrowienia od potomka\n");
            break;
        
        default: 
            printf("<parent> ja jestem PARENT\n");
            wait(&status);
            printf("<parent> potomek skończył, zwrócił: %d\n", status);
    }

    return 0;
}