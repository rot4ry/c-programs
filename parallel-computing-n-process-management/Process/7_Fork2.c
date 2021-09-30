#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include <sys/wait.h>

int main(){
    int status;
    switch( fork() )
    {
        case -1: 
            printf( "Błąd uruchomienia procesu potomnego \n" ); 
            break;
        
        case  0:
            printf( "** URUCHOMIENIE PROCESU POTOMNEGO **\n" );
            execl("/usr/bin/free", "-m", '\0' );
            printf( "Błąd w procesie potomnym\n" );  
            exit( -1 );
            break; 
        
        default: 
            wait( &status );
            if( !status ) {
                printf( "potomek zakończył działanie (prawidłowo)\n" );
            }
            else {
            printf( "... coś nie tak z potomkiem\n" ); 
            }
    }
return 0;
}