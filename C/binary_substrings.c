/*  Antonio Leonti
    7.23.2020
    https://practice.geeksforgeeks.org/problems/binary-string-1587115620/1
*/
#include <stdio.h>
#include <stdlib.h>
/*  I think this is the best way to do it. The number of substrings which can
    start with each '1' in a binary string is that '1's distance from the
    zeroth digit.
*/
int solve(int x){
    int result = 0;
    // i = current digit's distance from zeroth digit
    for(int i = 1; x; i++, x>>=1){
        // if current digit is '1', multiply it by i and add this to result
        result += (x%2) * i;
    }
    return result;
}

int main(int argc, char** argv){

    for(int i = 1; i < argc; i++){
        // parse input
        int in = atoi(argv[i]);
        // find & print result
        printf( "%d. %d's binary string has %d substrings starting with 1.\n",
                i, in, solve(in)                                             );
    }
}
