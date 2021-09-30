#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <math.h>

int main(){
    int pid, status;
    int one[2];
    int two[2];
    double x = 1.0;
    double y = 1.0;

    printf("\t[%d] parent, start\n\n", (int)getpid());
    if(pipe(one) < 0 || pipe(two) < 0){
        printf("Pipe error!");
        exit(1);
    }

    switch(pid = (int)fork())
    {
        case -1: 
            printf("Fork error!");
            exit(1);
        break;

        case 0:
            printf("\t[%d] child, start \n\n", (int)getpid());
            close(one[1]);
            close(two[0]);
            read(one[0], (void*)&x, sizeof(double));
            printf("\t[%d] received x = %f\n", (int)getpid(), x);
            y = x * M_PI;
            printf("\t[%d] executed f(x)=y, sending y = %f\n", (int)getpid(), y);
            write(two[1], (void*)&y, sizeof(double));
            printf("\t[%d] child, stop\n\n", (int)getpid());
            exit(0);
        break;

        default:
            close(one[0]);
            close(two[1]);
            printf("\t[%d] sends to child [%d] x=%f\n\n", (int)getpid(), pid, x);
            write(one[1], (void*)&x, sizeof(double));
            read(two[0], (void*)&y, sizeof(double));
            wait(&status);
            printf("\t[%d] child ended with code [%d]\n", pid, status);
            printf("\t[%d] received y=%f\n", (int)getpid(), y);
            printf("\t[%d] parent, stop\n\n", (int)getpid());
    }
    return 0;
}