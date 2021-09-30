#include <unistd.h>
#include <stdio.h>

int main()
{
    char *arg[4];
    arg[0] = "pierwszy";
    arg[1] = "drugi";
    arg[2] = "trzeci";
    arg[3] = '\0';
    

    printf("-Wywolanie (samobojcze) potomka --------------\n");
    execv("./child", arg);

    return 0;
}