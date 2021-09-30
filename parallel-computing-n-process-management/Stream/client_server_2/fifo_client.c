#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>

int empty(char* input){
    while(*input){
        if(isalnum(*input++)){
            return 0;
        }
    }
    return 1;
}

int main(){
    FILE* stream;
    char buffer[LINE_MAX];
    int run = 0;

    if((stream = fopen("channel", "r+"))) run = 1;
    else perror("Error while opening connection.");

    while(run){
        bzero((void*)buffer, LINE_MAX);
        fgets(buffer, LINE_MAX, stdin);
        if(!empty(buffer)){
            fprintf(stream, "%s", buffer); 
            fflush(stream);
        }
        
        else{
            fclose(stream);
            break;
        }
        fgets(buffer, LINE_MAX, stream);
        
        if(!empty(buffer)){
            fprintf(stdout, "%s", buffer);
            fflush(stream);
        }
    }
    return 0;
}