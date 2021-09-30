#include <stdio.h>
#include <limits.h>

int main(){
    FILE* stream;
    char buffer[LINE_MAX];
    int run = 0;

    if((stream = fopen("channel", "r+"))) run = 1;
    else perror("Error while opening connection.");

    while(run){
        if(fgets(buffer, 256, stream))
        {
            fprintf(stream, "%s", buffer);
            fflush(stream);
        }
    }
    return 0;
}