#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/stat.h>

int main(int argc, char **argv){
    
    int nsems;          //ilosc semaforow w tworzonym zbiorze
    int semflag;        //maska semaforow
    key_t key;          //klucz 

    if(argc > 1)
    {
        sscanf(argv[1],"%d", &nsems);
        if(nsems > 0) 
        {
            key = ftok("~/Desktop", 'a'+'t'+'h'+'r'+'i'+'r');
            printf("[pid = %u] tworzy zbior %d semaforow [key = %x]\n", 
                    (unsigned)getpid(), nsems, (unsigned)key);
            
            semflag = IPC_CREAT | S_IRUSR | S_IWUSR;

            if( semget(key, nsems, semflag) ==  -1 )
            {
                perror("\t semget error()!");
                exit(3);
            }            
        }
        else
        {
            printf("\tbledna ilosc semaforow (n = %d)\n", nsems);
            exit(2);
        }
    }
    else
    {
        printf("\t%s [%s] \n%s", argv[0], "n", "\tn -rozmiar tworzonej tablicy semaforow\n");
        exit(1);
    }

    return 0;
}
