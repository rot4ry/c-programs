#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
    int fd[2];
    int pid, status;
    FILE* stream;

    if(pipe(fd) < 0)
    {
        printf("Pipe error!\n");
        exit(1);
    }

    switch((pid = (int)fork())){
        case -1:
            perror("Fork error!");
            exit(1);
        break;

        case 0:
            printf("\tDescendant [%d] starting...\n", (int)getpid());
            close(fd[1]);
            dup2(fd[0], STDIN_FILENO);
            close(fd[0]);
            printf("------------------------------------------------------------\n");
            execl("/usr/bin/sort", "sort", "--reverse", (char*)NULL);
        break;

        default: 
        close(fd[0]);
        stream = fdopen(fd[1], "w");
        fprintf(stream, "\tAaaaa\n");
        fprintf(stream, "\tBbbbbbb\n");
        fprintf(stream, "\tCcccccccc\n");
        fprintf(stream, "\tDdddddddddd\n");
        fflush(stream);
        close(fd[1]);
        wait(&status);
        printf("------------------------------------------------------------\n");
        printf("\tDescendant [%d] ended with status %d\n", pid, status);
    }
    return 0;
}