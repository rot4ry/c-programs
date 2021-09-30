#include "dependencies.h"

int main()
{
    char* WORD = NULL;
    size_t length = 0;
    ssize_t read = 0;
    read = getline(&WORD, &length, stdin);
    if(read == -1){
        perror("Input error.");
        exit(-10);
    }
    size_t WORD_LENGTH = strlen(WORD);
    printf("Building suffix tree...\n");
    SUFFIX_TREE* WORD_TREE = ST_CreateTree(WORD, WORD_LENGTH);
    printf("Building suffix tree finished...\n");
    
    if(WORD_TREE != NULL){ 
        search_for_repeating_prefix(WORD_TREE, WORD, WORD_LENGTH);
    }
    else{ 
        perror("Error occured during building the suffix tree.");
        exit(-1); 
    }
    return 0;
}