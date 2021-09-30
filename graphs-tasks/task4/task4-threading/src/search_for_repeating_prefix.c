#include "dependencies.h"

size_t _REPEATED_PREFIX_LENGTH = 0;
SUFFIX_TREE* global_tree;

void search_for_repeating_prefix(SUFFIX_TREE* tree, char* base_word, size_t word_length){

    global_tree = tree;

    size_t _MAX_PREFIX_LENGTH;
    if(word_length%2 == 0) {    _MAX_PREFIX_LENGTH = word_length/2;     }
    else                   {    _MAX_PREFIX_LENGTH = (word_length-1)/2; }
    
    printf("Maximum prefix length = %lu\n", _MAX_PREFIX_LENGTH);
    printf("Searching...\n");
    
    pthread_t _THREADS[_MAX_PREFIX_LENGTH]; //bez 0 indeksu 
    char* repeating_prefix  = malloc(2);
    char* thread_input      = malloc(strlen(repeating_prefix));

    for(size_t PREFIX_LENGTH = 1; PREFIX_LENGTH <= _MAX_PREFIX_LENGTH; PREFIX_LENGTH++){

        printf("%lu\n", PREFIX_LENGTH);
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
        strcat(repeating_prefix, "\0");
        
        //pthread_mutex_lock?
        //<this> -> new thread        
        char* thread_temporal = realloc(thread_input, (2*PREFIX_LENGTH)+1);
        if(thread_temporal){
            thread_input = thread_temporal;
            memset((char*)thread_input, 0, strlen(thread_input));
        }
        else{
            perror("realloc() error, memory leak incoming.");
            exit(-2);
        }
        strcpy(thread_input, repeating_prefix);
        if(pthread_create(&_THREADS[PREFIX_LENGTH], NULL, divide_and_conquer, (void*)thread_input))
        {
            perror("pthread_create() error.");
            exit(-25);
        }
        free(thread_temporal);
        //</this>
    }

    for(pthread_t tid = 1; tid<=_MAX_PREFIX_LENGTH; tid++){
        
        if(pthread_join(_THREADS[tid], NULL))
        {
            perror("pthread_join() error.");
            exit(-5);
        }
    }

    if(_REPEATED_PREFIX_LENGTH > 0){
       printf("\nLongest repeating prefix length = %lu\n", _REPEATED_PREFIX_LENGTH);
    }
    else{
       printf("\nNo repeating prefix found.\n");
    }
}

void* divide_and_conquer(void* prfx){

    char* _prefix = prfx;

    size_t found_position = ST_FindSubstring(global_tree, _prefix, strlen(_prefix));
    if(found_position == 1){
       _REPEATED_PREFIX_LENGTH = strlen(_prefix);
    }
    pthread_exit(NULL);
}