#include "dependencies.h"

size_t _REPEATED_PREFIX_LENGTH = 0;

void search_for_repeating_prefix(SUFFIX_TREE* tree, char* base_word, size_t word_length){

    size_t _MAX_PREFIX_LENGTH;
    if(word_length%2 == 0) {    _MAX_PREFIX_LENGTH = word_length/2;     }
    else                   {    _MAX_PREFIX_LENGTH = (word_length-1)/2; }
    
    printf("Maximum prefix length = %lu\n", _MAX_PREFIX_LENGTH);
    printf("Searching...\n");
    
    char* repeating_prefix = malloc(2);

    for(size_t PREFIX_LENGTH = 1; PREFIX_LENGTH <= _MAX_PREFIX_LENGTH; PREFIX_LENGTH++){

        char* temporal_pointer = realloc(repeating_prefix, (2*PREFIX_LENGTH)+1);
        if(temporal_pointer){
            repeating_prefix = temporal_pointer;
            memset((char*)repeating_prefix, 0, strlen(repeating_prefix));
        }
        else{
            perror("realloc() error, memory leak incoming.");
            exit(-2);
        }
        strncpy(repeating_prefix, base_word, PREFIX_LENGTH);
        strncat(repeating_prefix, base_word, PREFIX_LENGTH);
        size_t found_position = ST_FindSubstring(tree, repeating_prefix, strlen(repeating_prefix));

        if(found_position == 1){
           _REPEATED_PREFIX_LENGTH = strlen(repeating_prefix);
           printf("UPDATE");
        }
        getchar();
    }

    if(_REPEATED_PREFIX_LENGTH > 0){
       printf("\nLongest repeating prefix length = %lu\n", _REPEATED_PREFIX_LENGTH);
    }
    else{
       printf("\nNo repeating prefix found.\n");
    }
}
