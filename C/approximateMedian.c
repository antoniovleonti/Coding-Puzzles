/*  Antonio Leonti
    9.2.2020 (First day of F20 semester!)
    "Approximate Median" - not exactly following the "rubric" though
    https://programmingpraxis.com/2020/08/21/approximate-median/
*/

#include <stdio.h>
#include <stdlib.h>

float newAvg(float, unsigned*, float);

int main(void){
    char input[100], avg_str[100]; // general purpose string
    unsigned cnt = 0;
    float avg;

    while(1){
        printf(
            "\nCount: %d | Average: %s\nEnter a number ('Q' to quit).\n\t> ",
            cnt, cnt ? avg_str : "----" // there is no average initially
        );

        fgets(input, 99, stdin); // take input

        if(input[0] == 'Q' || input[0] == 'q') break;

        avg = newAvg(avg, &cnt, atof(input)); // recalculate average
        sprintf(avg_str, "%-.2lf", avg);      // create output string
    }
}
/*  avg is current average
    cnt is the number of terms used to calculate that average
    new is the new number to be included in the average
*/
float newAvg(float avg, unsigned* cnt, float new){
    return (avg * *cnt + new) / ++*cnt;
}
