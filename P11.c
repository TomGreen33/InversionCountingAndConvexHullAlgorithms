/* Name: Thomas Green
 * ID: 1048389
 * Assignment #: 2
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


int getNumInversionsBruteForce(int *A, int n);


/* Computes the number of inversions in array A
 * @param A: Array A in which inversions need to be counted
 * @param n: Size of array A
 * @return the number of inversions in array A
 */
int getNumInversionsBruteForce(int *A, int n) {

  int numInversions;
  int i;
  int j;

  numInversions = 0;

  /* For every element */
  for (i = 0; i < n-1; i++)
  {
    /* For every element in front of a given element,
     * if there is a miss match, increment numInversions by 1 */
    for (j = i+1; j < n; j++)
    {
      if ((int)*(A+i) > (int)*(A+j))
      {
        numInversions++;
      }
    }
  }
  
  return numInversions;
}
