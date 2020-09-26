/*  Antonio Leonti
    9.22.2020
    CIS 360
    Variadic search - like binary search, but n-ary
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int variadic_search(int*, int, unsigned, int, int);
int cmpfunc(const void*, const void*); // util for stdlib's qsort()

int main(void){
    srand((unsigned)time(0));

    char result_str[100]; // string representation of result
    int result, key = rand() % 100;

    // create sorted array A where 0 <= A_i < 100
    int A[100];
    for(int i=0; i<100; i++) A[i] = rand() % 100;   // set to random numbers
    qsort(A, 100, sizeof(int), cmpfunc);            // sort

    // print some stuff
    for(int i=0; i<50; i++) putchar('-');                   // ---
    printf("\nvariadic_search() demo:\n\nA[100] = \n{\t");  // title
    for(int i=0; i<100; i++)
        printf("%2d,%s", A[i], !i||(i+1)%10?" ":"\n\t");    // the array

    // get result and string representation of result
    result = variadic_search(A, key, 3, 0, 99);
    sprintf(result_str, "%d", result);

    // print results
    printf( "\r}\nindex of %d in A[] = %s\n\n",
            key, result == -1 ? "(not found)" : result_str
    );
    for(int i=0; i<50; i++) putchar('-');
}

/*
    "Write an algorithm that searches a sorted list of n items by dividing it into three sublists of almost n/3 items. This algorithm finds the sublist that might contain the given item and divides it into three smaller sublists of almost equal size. The algorithm repeats this process until it finds the item or concludes that the item is not in the list. Analyze your algorithm and give the results using order notation."

    This function allows for unary, binary, ternary, quaternary, ..., n-ary search. "Arity" is the number of times each sub-array is split. For the purpose of this assignment, arity=3. Generalizing to n-ary search does not increase the time complexity for arity=3. I originally coded it as ternary search, then realized I could generalize by just changing every '3' to 'arity'.
*/
int variadic_search(int* A, int key, unsigned arity, int lo, int hi){
    // hi <= 0 → key < min(A) → key ∉ A
    // arity must be > 0 otherwise we'll divide by zero later
    if(hi>0 && arity){
        // I[] contains all indices
        for(int i=0, I[arity+1]; i<=arity; i++){
            // calculate and store index
            I[i] = lo + (hi-lo)*i / arity;
            // check current index for key -- base case!
            if(A[I[i]] == key) return I[i];

            if(A[I[i]] > key){
                // key would be in previous partition--narrow search
                return variadic_search(A, key, arity, I[i-!!i*1], I[i]-1);
            }
        }
    }
    return -1;
}

//  comparison function for qsort()
int cmpfunc(const void* a, const void* b){
   return *(int*)a - *(int*)b;
}
