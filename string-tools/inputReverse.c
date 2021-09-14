#include "stringToInt.h"

void inputReverse(char* input)
{
    int lenght = strlen(input)-1;
    char reversed[lenght];

    for(int i=0; i<=lenght; i++)
    {
        reversed[i]=input[lenght-i];
    }
    for(int i=0; i<=lenght; i++)
    {
        input[i]=reversed[i+1];
    }
    //return input;
}
