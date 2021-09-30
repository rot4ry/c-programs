#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>

int main(){
    time_t stamp;
    pid_t pid;
    int fd;
    int run = 0;
    char cmd;

    printf("[%d] SERVER [%d]\n", (int)getpid(), (int)getpid());

    if((fd = open("pipe", O_RDONLY)) > 0) {
        run = 1;
    }
    else {
        printf("Connection not found.\n");
    }

    while(run){
        read(fd, &pid, sizeof(pid_t));
        read(fd, &cmd, sizeof(char));
        stamp = time(NULL);
        printf("[%d]\t|%c| -> %s", (int)pid, cmd, ctime(&stamp));
        if(cmd == 'Q'){
            run = 0;
            close(fd);
        }
    }
    return 0;
}