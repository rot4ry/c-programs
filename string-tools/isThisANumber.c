#include "stringToInt.h"

int isThisANumber(char* input)
{
    char numbers[10]={'0','1','2','3','4','5','6','7','8','9'};
    int yayOrNay=0;
    
    for(int i=0; i<strlen(input)-1; i++)
    {
        for(int j=0; j<10; j++)
        {
            if(input[i]==numbers[j])
            {
                yayOrNay=1;
                break;
            }
            else if(input[0]=='-')
            {
                yayOrNay=1;
                break;
            }
               
            else  
            {
                yayOrNay=0;
            }
        }
        if(yayOrNay==0)
        break;
    }
    return yayOrNay;
}