//parent - excl
#include <unistd.h>
#include <stdio.h>

int main()
{
    char *arg1 = "first";
    char *arg2 = "second";
    char *arg3 = "third";
    printf("\n");
    execl("./child", arg1, arg2, arg3, '\0');
    
    return 0;
}