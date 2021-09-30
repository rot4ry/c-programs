#include <stdio.h>

int main(int argc, char **argv)
{
    printf("\n");
    for(int i=0; i<argc; i++)
    {
        printf("%4d: _____ %s\n", i, argv[i]);
    }

    return 0;
}