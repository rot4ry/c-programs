#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/msg.h>
#include <time.h>

#define PROJECTID 666

int main(){
    
    key_t key;
    int flag;
    int msqid;
    struct msqid_ds buffer;

    key = ftok("/home/rot4ry/Desktop", PROJECTID);
    flag = IPC_CREAT | 256 | 128;

    msqid = msgget(key, flag);

    if(msqid < 0)
    {
        perror("Error msgget()!");
        exit(1);
    }

    else
    {
        if( !msgctl(msqid, IPC_STAT, &buffer) )       
        {
            printf("\tKolejka [%d]\n", (int)msqid);
            printf("\tMoje UID: %d\n \tMoje GID: %d\n", (int)getuid(), (int)getgid());
            printf("\n\t%s", ctime(&(buffer.msg_ctime)));
            printf("\tUID: %d\n \tGID: %d\n", (int)buffer.msg_perm.uid, (int)buffer.msg_perm.gid);

            printf( "\tKlucz key: 0x%x\n", buffer.msg_perm.__key );
            printf( "\tRozmiar kolejki: %lu B / %u MSG\n", buffer.msg_cbytes, (unsigned)buffer.msg_qnum);
            
            msgctl(msqid,IPC_RMID,&buffer ); //USUNIĘTO KOMENTARZ
        }

        else
        { 
            perror( "Error msgctl()"); 
            exit( 2 ); 
        }
    }   
    
    return 0;
}
 