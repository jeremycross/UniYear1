#include <stdio.h>
#include <stdlib.h>

struct d1{

    int id1;
    char c1;
    int id2;
    char c2;

};

int main(){

    printf("%lu\n", sizeof(struct d1));

    printf("%lu\n", sizeof(long int));

    return 0;

}
