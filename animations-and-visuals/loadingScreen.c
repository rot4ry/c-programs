#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{

    int a[50]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    
    int counter=1;

        for (int b = 0; b<=49 ;b++)
        {   
		printf("\v\v\t\t");
            if(b==49)
            {    
                b=0;
            }

            a[b]=1;
            
            for(int j=0; j<=48;j++)
            {
                if(a[j]==1)
                {
                    switch(counter)
                    {
                        case 1: printf("L");
                                break;
                        case 2: printf("O");
                                break;
                        case 3: printf("A");
                                break;
                        case 4: printf("D");
                                break;
                        case 5: printf("I");
                                break;
                        case 6: printf("N");
                                  break;
                        case 7: printf("G");
                                break;
                        default:printf("-"); 
				counter = 0;
                                break;
                    }
                    counter++;
    
                }
                else
                {
                    printf("-");
                }
                
            }
            printf("\n");
            system("sleep 0.25s");
            system("clear");
            
            a[b]=0;
              
        }
    return 0;
}       
