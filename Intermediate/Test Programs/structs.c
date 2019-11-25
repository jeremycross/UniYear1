#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct student {
    int id;
    char name[20];
    float percentage;
};

int main() {
    struct student *record;
    struct student rep;

    record = &rep;

    record[0].id=1;
    strcpy(record[0].name, "Raju");
    record[0].percentage = 86.5;

    printf(" Id is: %d \n", record->id);
    printf(" Name is: %s \n", record->name);
    printf(" Percentage is: %f \n", record->percentage);

    return 0;
}
