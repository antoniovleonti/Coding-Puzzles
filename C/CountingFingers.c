/*  Antonio Leonti
    7.20.2020
    https://programmingpraxis.com/2020/06/16/counting-fingers/

    A little girl counts on her fingers in a curious way. She counts 1 on her
      thumb, 2 on her index finger, 3 on her middle finger, 4 on her ring
      finger, and 5 on her pinkie finger, then works back, counting 6 on her
      ring finger, 7 on her middle finger, 8 on her index finger, and 9 on her
      thumb, when she again turns around and counts 10 on her index finger, 11
      on her middle finger, and so on.

    Your task is to write a program that determines which finger the little
      girl will be on when she reaches a thousand. When you are finished, you
      are welcome to read or run a suggested solution, or to post your own
      solution or discuss the exercise in the comments below.
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*  Returns a finger 0-4, with 0 being the thumb, and 4 being the pinky.
    Calculates finger using the absolute value of a triangle wave
*/
int finger(int x){
    return (int)(fabs(8/M_PI * asin( sin(M_PI*(x-1) / 8 ))) + 0.5);
}

int main(){
    printf("She counts 1000 on her %c finger.\n", "timrp"[finger(1000)]);
}
