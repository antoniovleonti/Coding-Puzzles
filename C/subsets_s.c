/*  Antonio Leonti
    CIS 360 (not really, though--unassigned exercise)
    9.5.2020
    Print all subsets of size k of a set of n elements. (subsets_s())
*/

#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

char** subsets_s(char*, const unsigned);
char* strToSet(char*);
unsigned long long nextKBitMask(int);
int fac(int);

int main(void)
{
    char str[100] = "ANTONIO"; // user-defined stuff
    unsigned len = 3;

    char* set = strToSet(str); // get results
    char** subs = subsets_s(set, len);

    printf("String:\n\t\"%s\"\nSet:\n\t\"%s\"\nSubsets:\n{", str, set);
    for(int i = 0; subs[i][0]; i++)
    {
        printf("\t\"%s\"\n", subs[i]);
        free(subs[i]); // free each subset
    }
    printf("}\n"); // print results

    free(set); // free malloc'ed arrays
    free(subs);
}
/*  subsets_s returns an array of all subsets of size K of a char[] 'set'.
    Terminated with a null set, removing the need for a count parameter.
    Named after "sprintf_s()" which takes an additional "size" parameter.
    "set" should be less than 64 characters (long long ints have 64 bits).
*/
char** subsets_s(char* set, const unsigned K)
{
    int N_s = strlen(set);                      // # of elements in the set
    int N_r = fac(N_s) / (fac(K)*fac(N_s-K));   // # of subsets of length K

    char** ret = malloc((N_r+1) * sizeof(char*));   // return array

    unsigned long long mask = 0;                    // binary mask
    for(int i=0; i<K; i++) mask = (mask << 1) | 1;  // first subset's mask

    for(int i = 0; i < N_r; i++) // for each subset...
    {
        ret[i] = malloc(K+1); // allocate memory for this subset

        for(int tmp=mask, j=0, k=0; tmp; tmp>>=1, k++)
        {   // copy elements to subset which correspond to mask's set bits
            if(tmp&1) ret[i][j++] = set[k];
        }
        ret[i][K] = 0;              // terminate each subset with '\0'
        mask = nextKBitMask(mask);  // find next mask with K set bits
    }
    ret[N_r] = malloc(1); // Terminate return array with null set
    *ret[N_r] = 0;

    return ret;
}
/*  Removes duplicate elements in a string, leaving the first occurance of each.
*/
char* strToSet(char* str)
{
    char* cpy = strcpy(malloc(strlen(str)), str); // preserve original
    // hash = running count of each char; gap = # of duplicates
    unsigned hash[CHAR_MAX] = {0}, gap = 0;

    for(int i=0; cpy[i-gap]; i++) // for each character...
    {
        if(gap) cpy[i-gap] = cpy[i]; // move backward by # of duplicates found
        gap += !!hash[cpy[i]]++;     // increase gap if this char is a duplicate
    }
    return cpy;
}
/*  Seeks next k-bit integer
    http://realtimecollisiondetection.net/blog/?p=78
*/
unsigned long long nextKBitMask(int n)
{
    unsigned long long b,c,m,t;

    b = n & -n; // extract lowest set bit b in x
    t = n + b; // shift lowest set bit to the left, here causing “jump” past two adjacent one bits
    c = n ^ t; // form "sufficiently long" sequence of one bits, for shifting down
    m = (c >> 2) / b; // form bitmask for the (two) bits we jumped past

    return t | m;
}
/*  Factorial.
*/
int fac(int n)
{
    return n>=1 ? n*fac(n-1) : 1;
}
