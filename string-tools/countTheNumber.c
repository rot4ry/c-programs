#include "stringToInt.h"

int countTheNumber(char* input)
{
    int lenght=strlen(input);
    int count=0;
    int number=0;
    

    for(int i=0; i<lenght; i++)
    {
        for(int j=0; j<10; j++)
        {
            if(input[i]==48+j)
            {
                number=j;
                break;
            }
        }
        count+=(number*pow(10,i));
        if(input[i+1]=='-')
        break;
    }
    if(input[lenght-1]=='-')
    {
    count=(-1)*count; 
    }
    return count;
}
