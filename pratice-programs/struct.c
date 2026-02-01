/* struct.c */
#include <stdio.h>
#include <string.h>

// Define a structure to hold personal information
struct person{
    char title[8];
    char lastname[32];
    int age;
};

int main() {
    struct person me; // Declare a variable of type struct person

    strncpy(me.title, "Mr.", 7); // Assign title
    strncpy(me.lastname, "Sharma", 31); // Assign last name
    me.age = 21;

    printf("%s %s of the age %d\n",
        me.title, me.lastname, me.age);

    return 0;
}