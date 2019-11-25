#include <stdlib.h>
#include "compareElements.h"

int compare_money_ascending (const void *a, const void *b){
    /*returns the difference between the salary element in struct a and the salary element in struct b, if a.salary is less than b.salary returns a negative, they are in order*/
    return (((struct element*)a)->salary) - (((struct element*)b)->salary); /*Cast void pointer to struct element pointer to use*/
}

