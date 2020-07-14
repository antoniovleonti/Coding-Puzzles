/*  Antonio Leonti
    7.14.2020
    https://programmingpraxis.com/2020/07/14/13013/
    this program concatenates the bits of each int up to n
*/
#include <stdio.h>
#include <conio.h>
#include <math.h>

//concatenate the bits of b to the end of a
int bitcat(int a, int b){
    // make room for b at the end of a
    for(int i = b; i; i >>= 1) a <<= 1;
    // add b to the end
    return a | b;
}
// concatenate bits of every number up to & including a
int solve(int a){
    int ret;
    //starting at 0, concatenate each int to the end of ret up to a
    for(int i = ret = 0; i <= a; i++) ret = bitcat(ret, i);
    // this is actually the result modulo INT_MAX
    return ret;
}

int main(){
    // test numbers 0 - 10
    for(int i = 0; i < 10; i++){
        printf("%d -> %d\n", i, solve(i));
    }
    getch(); return 0;
}
