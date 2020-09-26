/*  Antonio Leonti
    7.18.2020
    https://programmingpraxis.com/2020/06/02/hidden-squares/
    Finds all the "sub integers" of an int which are squares
*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// returns length followed by each hidden square.
int* hiddenSquares(int x){
    int count = 0;
    int digits = 0;

    for(int i = x; i > 0; i /= 10) digits++; // count digits in x
    int tmp[digits*(digits+1)/2]; // set up temp array for values
    // digits*(digits+1)/2 is the max number of hidden squares there could be!

    for(int i = digits; i > 0; i--){
        x %= (int)(pow(10, i)+0.5); // remove leftmost digits of x

        for(int j = x; j > 0; j /= 10){ // remove rightmost digits
            float rt = sqrt(j); // take sqrt

            if(rt == (int)rt){ // if it's a perfect square...
                int exists = 0; // is j already in tmp? ...
                for(int k = 0; k < count && !exists; k++) exists = tmp[k]==j;
                if(!exists) tmp[count++] = j; // if not, add it!
            }
        }
    }
    // set up the return array
    int* ret = malloc((count+1) * sizeof(int)); // allocate return array
    for (int i = 1; i < count+1; i++) ret[i] = tmp[i-1]; // copy over values
    ret[0] = count; // count is the first number.

    return ret;
}

int main(int argc, char** argv){
    int len = argc-1;
    int input[len];
    //parse input
    for(int i = 1; i < argc; i++) input[i-1] = atoi(argv[i]);

    for(int i = 0; i < len; i++){
        // get hidden squares
        int* result = hiddenSquares(input[i]);
        // iterate thru and print results
        printf("%d. Hidden squares in %d:\n", i, input[i]);
        for(int j = 1; j < result[0]+1; j++) printf(" %d", result[j]);
        // finish it off with a newline!
        putchar('\n');
        // keep it tight
        free(result);
    }
}
