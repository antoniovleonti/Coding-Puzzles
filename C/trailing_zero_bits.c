/*  Antonio Leonti
    7.13.2020
    https://programmingpraxis.com/2020/07/07/trailing-zero-bits/
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

int solve(int);

int main(){
    int input = 0;
    int output = solve(input);

    printf("There are %d trailing zero-bits in %d.", output, input);

    getch(); return 0;
}

int solve(int n){
    int ret = 0;
    // the number of trailing zeros for 0 is the number of bits in an int.
    while(!(n % 2) && ret < 8 * sizeof(int)){ // If the last bit is 0
        n >>= 1; // shift bits to the right
        ret++; // and increase the return value by 1.
    }
    return ret;
}
