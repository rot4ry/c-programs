#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/msg.h>

#define MSGMAX 8192
#define PROJECTID 0x1A

int main( void )
{
    key_t key;
    unsigned int msqid;
    unsigned int pid;
    
    struct msqid_ds buffer;
    struct { 
        long type; 
        char text[MSGMAX]; 
    } message;
    
    key = ftok("/home/rot4ry/Desktop", PROJECTID);
    msqid = msgget(key, IPC_CREAT| 0x100 | 0x80);
    
    if( msqid<0 )
    {
        perror("Error msgget()!"); 
        exit(1); 
    }

    else
    {
        pid = getpid();
        printf("Proces [%u] utworzyl kolejke: %u\n", pid, msqid);
        
        //konstrukcja i wyslanie wiadomosci
        message.type = (long)pid;
        
        (void)strcpy(message.text, "Pierwsza wiadomosc.");  //
        printf("[%u] wysyla wiadomosc >>> \t%s\n", pid, message.text);
        msgsnd(msqid, (void*)&message, strlen(message.text)+1, IPC_NOWAIT);
        

        (void)strcpy(message.text, "To jest druga wiadomosc");// 
        printf("[%u] wysyla wiadomosc >>> \t%s\n", pid, message.text);
        msgsnd(msqid, (void*)&message, strlen(message.text)+1, IPC_NOWAIT);

        //odebranie wiadomosci
        while(msgrcv(msqid, (void*)&message, MSGMAX, pid, IPC_NOWAIT|MSG_NOERROR) > 0)
        {
            printf("Proces [%u] otrzymal wiadomosc <<< \t%s\n", pid, message.text);
            bzero((void*)&message,sizeof( message ));
        }

        msgctl(msqid, IPC_RMID, &buffer);
    }

    return 0;
}
