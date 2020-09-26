/*  Antonio Leonti
    7.17.2020
    https://projecteuler.net/problem=1
    sum all multiples of 3 or 5 under 1000.
*/
#include <stdio.h>

// general approach - takes an array of desired multiples & max
int solve1(int n, int* factor, int max){
    int sum = 0;

    for(int i = 0; i < max; i++){
        //iterate through factors
        for(int j = 0; j < n; j++){
            // if you find an i which is a factor of one of the numbers
            if(!(i % factor[j])){
                sum += i; // add it to the sum
                break;    // and go onto the next i
            }
        }
    }
    return sum;
}
// "quick and dirty" approach
int solve2(){
    int sum = 0;
    for(int i = 0; i < 1000; i++){
        // the !(...) turns into 0 if i is not divisible by 3 or 5.
        sum += i * !(i%3 && i%5);
    }
    return sum;
}

int main(){
    int factor[2] = {3,5};

    printf("1. The sum of multiples of 3 | 5 < 1000 = %d\n", solve1(2, factor, 1000));
    printf("2. The sum of multiples of 3 | 5 < 1000 = %d\n", solve2());
}
