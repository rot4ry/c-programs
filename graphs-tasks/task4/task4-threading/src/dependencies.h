#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <strings.h>

//Using suffix_tree library, available at the address: 
//http://www.quretec.com/u/vilo/edu/2002-03/Tekstialgoritmid_I/Software/Loeng5_Suffix_Trees/Suffix_Trees/cs.haifa.ac.il/shlomo/suffix_tree/
#include "suffix_tree.h"

void search_for_repeating_prefix(SUFFIX_TREE* tree, char* base_word, size_t word_length);
void* divide_and_conquer(void* prfx);