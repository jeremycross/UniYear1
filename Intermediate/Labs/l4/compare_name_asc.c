#include <stdlib.h>
#include <string.h>
#include "compareElements.h"

int compare_name_ascending (const void *a, const void *b){
    /*strcmp returns negative value if last_name in struct a is less than last_name in b (0 is they are equal and positive value is a is larger), if a is less than b they are in order*/
    return strcmp(((struct element*)a)->last_name, ((struct element*)b)->last_name); /*return the value of the comparison between a and b*/
}

