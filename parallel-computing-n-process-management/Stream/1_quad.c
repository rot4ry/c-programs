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

int main(){
    int pid, status;
    double a, b, I;
    unsigned int n;
    a = 0.0;
    b = 1.0; 
    I = 0.0;
    n = 3200;
    
    switch((int)fork()){
        case -1:    
            perror("Fork error!");
            exit(1);
        break;

        case 0: 
            I = quad(n, a, b, sine);
            printf("Process [%d] calculated value:\t%16.6f\n", (int)getpid(), I);
            exit(0);
        break;

        default:
            printf("[%d] working hard...\n", (int)getpid());
            pid = (int)wait(&status);
            printf("[%d] ended with code: %d\n", pid, status);
            printf("[%d] received value: \t%16.6f\n",(int)getpid(), I);
    }

    return 0;
}

