#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void bye();

int main(){
    int status;
    
    (void)atexit(bye);

    switch( fork() ){
        case -1: printf("Błąd uruchomienia procesu potomnego\n");
        break;

        case 0: exit(EXIT_SUCCESS);
        break;

        default:
        wait(&status);
        if(status){
            printf("Błąd powrotu\n");
            exit(EXIT_FAILURE);
        }
        atexit(bye);
        return EXIT_SUCCESS;
    }
}

void bye(void)
{
    printf("I to wszystko w [%d]\n", (int)getpid());
    return;
}