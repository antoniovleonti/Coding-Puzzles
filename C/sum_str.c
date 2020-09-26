/*  Antonio Leonti
    9.15.2020
    For Professor Valova
    190 puzzle - recursively sum all embedded integers in a string
*/

#include <stdio.h>
#include <string.h> // strcspn(), strspn(), strncpy()
#include <stdlib.h> // malloc()

char DIGITS[10] = "0123456789";

int sumStr(char*);

int main(void)
{
    char* str = "735fda89g1dfagd7";
    printf( "String:\n\t%s\nSum1:\n\t%d\nSum2:\n\t%d\n", str, sumStr1(str));
}

int sumStr(char* str)
{
    char* p;
    int start, len, n;

    start = strcspn(str, DIGITS); // find first string of numbers
    len = strspn(str+start, DIGITS);

    if(!len) return 0; // if no number exists, you're done. Otherwise...

    p = strncpy(malloc(len+1), str+start, len); // get integer substring
    n = atoi(p); free(p); // convert to number and free malloc'd array

    return n + sumStr(str+start+len); // move onto the next one
}
