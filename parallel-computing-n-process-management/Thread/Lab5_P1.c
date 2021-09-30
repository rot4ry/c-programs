#include <stdio.h>
#include <pthread.h>
#define ENDLESS 1

void* o(void* unused){
    (void)unused;

    while(ENDLESS){
        putchar('o');
    }
    return 0;
}

int main(){
    pthread_t threadID;
    pthread_create(&threadID, NULL, &o, NULL);

    while(ENDLESS){
        putchar('x');
    }

    return 0;
}


