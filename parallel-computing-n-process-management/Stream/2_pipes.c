#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/limits.h>

int main(){
    int fd[2], n;
    char line[PIPE_BUF];
    
    if(pipe(fd) < 0){
        printf("Error while opening the stream.\n");
        exit(1);
    }
    switch(fork()){
        case -1: 
            printf("Fork error!");
            exit(1);
        break;

        case 0:
            close(fd[0]);
            write(fd[1], "\n\t[Hello, this is a descendant!]\n\n", 34);
            close(fd[1]);
            exit(0);
        break;

        default:
            close(fd[1]);
            n = read(fd[0], (void*)line, PIPE_BUF);
            write(STDOUT_FILENO, line, n);
    }
    return 0;
}