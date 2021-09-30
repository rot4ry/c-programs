#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <math.h>

double sine(double x)
{ 
    return sin(2 * M_PI * x) * exp(-x); 
}

double quad(unsigned int n, double a, double b, double (*fun)(double)){
    
    double xk, sum;
    sum = fun(a) + fun(b);
    for(int k=1; k<n; k++){
        xk = a + (b-a) * k/n;
        sum += 2.0 * fun(xk);
    }
    
    return ((b-a)/(2.0 * n) * sum);
}


int main()
{
    int pid, status;
    unsigned int n;
    double a, b, I;
    int fd[2];
    a = 0.0;
    b = 1.0;
    I = 0.0;
    n = 3200;

    if(pipe(fd) < 0){
        printf("Error while opening the stream.\n");
        exit(1);
    }

    switch(fork()){
        case -1:
            perror("Fork error!");
            exit(1);
        break;

        case 0:
            close(fd[0]);
            I = quad(n, a, b, sine);
            printf("Process [%d] ended with value %16.6f\n", (int)getpid(), I);
            write(fd[1], (void*)&I, sizeof(double));
            exit(0);
        break;

        default:
            close(fd[1]);
            printf("[%d] working hard...\n", (int)getpid());
            read(fd[0], (void*)&I, sizeof(double));
            printf("Process [%d] ended with code %d\n", (int)getpid(), status);
            printf("Process [%d] received value %16.6f\n", (int)getpid(), I);
    }
    return 0;
}