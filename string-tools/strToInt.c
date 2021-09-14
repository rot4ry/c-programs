#include "stringToInt.h"

int strToInt(char* input)
{
    int converted=0;
    
    for(int i=0; i<strlen(input); i++)
    {
        for(int j=0; j<=127; j++)
        {
            if(input[i]==(char)j)
            {
                converted+=j;
            }
        }
    }
    return converted;
}
