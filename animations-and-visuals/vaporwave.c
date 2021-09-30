//A simple and easy way to convert everything to v a p o r w a v e. 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* *argv)
{
    system("clear");
    printf("\t\v\v\t");
    for(int i=0; i<argc; i++)
    {
        for(int j=0; j<=strlen(argv[i]); j++)
        {
            if(i==0)
            {
                printf("%c ", argv[i][j]);    
            }

            else
            printf("%c  ", argv[i][j]);
        }

        if(i==0)
        {
            printf("\n\n\t\t\t");
        }
        else 
        printf("    ");
    }
    getchar();
    return 0;
}
