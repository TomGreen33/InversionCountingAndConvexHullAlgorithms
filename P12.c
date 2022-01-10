/* Name: Thomas Green
 * ID: 1048389
 * Assignment #: 2
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>


int getNumInversionsDivideAndConquer(int *A, int n);
int split(int *A, int *sortedA, int B, int C);
int count(int *A, int *sortedA, int bLower, int bUpper, int cUpper);


/* Computes the number of inversions in array A
 * @param A: Array A in which inversions need to be counted
 * @param n: Size of array A
 * @return the number of inversions in array A
 */
int getNumInversionsDivideAndConquer(int *A, int n) {

  int* sortedA;

  sortedA = (int*)malloc( n * sizeof(int) );

  return split(A, sortedA, 0, n-1);
}


/* Computes the number of inversions for a given subarray
 * @param A: Array A
 * @param B: Index of the first element of subarray B once it is defined
 * @param C: Index of the last element of subarray C once it is defined
 * @return the number of inversions in subarray
 */
int split(int *A, int *sortedA, int B, int C) {

  int bLower;
  int bUpper;
  int cLower;
  int cUpper;
  int numInversions;

  numInversions = 0;

  bLower = B;
  cLower = floor((B+C)/2);
  bUpper = floor((B+C)/2) + 1;
  cUpper = C;

  /* Ensure that the subarrays do not get smaller than size 1 */
  if (B < C)
  {
    /* Count the number of inversions in the current combined subarrays */
    numInversions += split(A, sortedA, bLower, cLower);
    numInversions += split(A, sortedA, bUpper, cUpper);
    numInversions += count(A, sortedA, bLower, bUpper, cUpper);
  }

  return numInversions;
}


/* Computes the number of inversions between subarrays B and C
 * @param A: Array A in which inversions need to be counted
 * @param sortedA: Array A after it is sorted
 * @param B: Subarray B
 * @param C: Subarray C
 * @return the number of inversions between subarrays B and C
 */
int count(int *A, int *sortedA, int bLower, int bUpper, int cUpper) {

  int i;      /* Pointer to subarray B                           */
  int j;      /* Pointer to subarray C                           */
  int k;      /* Pointer to sortedA                              */
  int count;  /* Number of inversions the the combined subarrays */

  /* Initialization of pointers */
  i = bLower;
  k = bLower;
  j = bUpper;

  count = 0;

  while (i < bUpper && j < cUpper + 1)
  {
    /* If there is no inversion, copy from B to sortedA, increment i and k */
    if (*(A + i) <= *(A + j))
    {
      *(sortedA + k) = *(A + i);
      k++;
      i++;
    }
    /* If there is an inversion, copy from C to A, increment j and k
     * and add the number of elements between the element pointed by i and first element of C to numInversions */
    else
    {
      *(sortedA + k) = *(A + j);
      k++;
      j++;

      count += bUpper - i;
    }
  }

  /* Copy the remaining elements of subarray B to sortedA */
  while (i < bUpper)
  {
    *(sortedA + k) = *(A + i);
    k++;
    i++;
  }

  /* Copy the remaining elements of subarray C to sortedA */
  while (j < cUpper + 1)
  {
    *(sortedA + k) = *(A + j);
    k++;
    j++;
  }

  /* copy elements from sortedA to A */
  for (i = bLower; i < cUpper + 1; i++)
  {
    *(A + i) = *(sortedA + i);
  }

  return count;
}
