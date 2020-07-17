/*  Antonio Leonti
    5.30.2020
    Finds the substring containing the most vowels
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

//uses the other functions to find substring with the most values
char* vowelestSubstr(char*, int);
//masks the first string with the characters in the second string
int* mask(char*, char*);
//creates a substring of a string
char* substr(char*, int, int);

int main(){
    char* string = "abcdefghijklmnopqrstuvwxyz";
    int length = 10;

    char* result = vowelestSubstr(string, length);
    printf(result);

    free(result); //keep a tight ship.

    getch(); return 0;
}
/*  s is an input string
    length is the length of the substring to be created
    returns the substring of the specified length which contains the most vowels
*/
char* vowelestSubstr(char* s, int length){
    int slen = strlen(s);
    int max = 0;
    //replace vowels with 1s, other with 0s
    int* isVowel = mask(s, "aeiou");
    //keeping track of each possible substring's vowel count seperately
    int* sum = calloc(slen-length, sizeof(int));

    for(int i = 0; i < slen-length; i++){
        for(int j = 0; j < length; j++){

            sum[i] += isVowel[i+j];
        }
        if(sum[i] > sum[max]) max = i;
    }
    free(isVowel); //this was dynamically allocated

    if(sum[max]){
        return substr(s, max, length);
    }
    //if there are no vowels, return null.
    return sum[max] ? substr(s, max, length) : '\0';
}
/*  s is the string to be masked
    m is a string containing all characters to allow through the mask
    returns an array of 0s and 1s, 1s being characters matching those in m
*/
int* mask(char* s, char* m){
    int slen = strlen(s); //length of string to be masked
    int mlen = strlen(m); //length of masking string
    //preallocate space for mask & initialize to 0
    int* ret = calloc(slen, sizeof(int));

    for(int i = 0; i < slen; i++){
        for(int j = 0; j < mlen; j++){
            //compare each value in s to each value in m
            if(s[i] == m[j]){
                //could just do ret[i] = s[i]==m[i] but this break statement saves time
                ret[i] = 1;
                break;
            }
        }
    }
    return ret;
}
/*  s is the string to make a substring of
    start is the substring's 0th index
    length is the length of the substring
    returns s[start..start+length]
*/
char* substr(char* s, int start, int length){
    int slen = strlen(s);

    if(slen < start+length){ //if invalid substring, return nothing
        return '\0';
    }
    //preallocate space for substring (+1 for the null terminator)
    char* ret = malloc((length+1) * sizeof(char));

    for(int i = 0; i < length; i++){
        ret[i] = s[start+i]; //copy over characters
    }
    ret[length] = '\0'; //top it off with null terminator

    return ret;
}
