/* Name: Thomas Green
 * ID: 1048389
 * Assignment #: 2
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <unistd.h>


int getNumInversionsBruteForce(int *A1, int n);
float** getConvexHullBruteForce(float **S, int n);
float** conqerConvexHull(float **S, int n);
int getNumInversionsDivideAndConquer(int *A, int n);
int computeTriangleArea(int x1, int y1, int x2, int y2, int x3, int y3);


int main (int argc, char *argv[]) {

  FILE *fp;
  int *A;
  int nA;
  float **S;
  int numInversions;
  int numInversions2;
  float **convexHull;
  int numExtreme;
  int nS;
  int i;
  int selection;
  double executionTime;
  clock_t begin;
  clock_t end;
  printf("The following file has been supplied to the program: %s\n\n", argv[1]);

  executionTime = 0;


  printf("*========================================================================*\n");
  printf("|   Option 1: Test brute force inversion counting algorithm with file    |\n");
  printf("|   Option 2: Test brute force inversion counting algorithm manually     |\n");
  printf("|   Option 3: Test smart inversion counting algorithm with file          |\n");
  printf("|   Option 4: Test smart inversion counting algorithm manually           |\n");
  printf("|   Option 5: Test brute force convex hull finding algorithm with file   |\n");
  printf("|   Option 6: Test brute force convex hull finding algorithm manually    |\n");
  printf("|   Option 7: Test smart convex hull finding algorithm with file         |\n");
  printf("|   Option 8: Test smart convex hull finding algorithm manually          |\n");
  printf("*========================================================================*\n\n");

  printf("Please make a selection: ");
  scanf("%d", &selection);

  if (selection < 1 || selection > 8)
  {
    printf("Invalid selection\n");
    return 0;
  }

  /* --------------- Inversions Counting --------------- */


  if (selection == 1 || selection == 3)
  {
    A = (int*)malloc(sizeof(int));
    i = 0;
    fp = fopen(argv[1], "rb");
    if (fp == NULL)
    {
        printf("Please enter a valid file name when executing the program and chosing this option\n");
        return 0;
    }

    while (!feof (fp))
    {
      i += 5;
      A = (int*)realloc(A, i * sizeof(int));
      fscanf(fp, "%d %d %d %d %d\n", A+i-5, A+i-4, A+i-3, A+i-2, A+i-1);
    }
    nA = i;
    fclose(fp);
  }
  else if (selection == 2 || selection == 4)
  {
    printf("Enter number of elements for the array: ");
    scanf("%d", &nA);
    printf("\n");

    A = (int*)malloc(nA * sizeof(int));

    for(i = 0; i < nA; ++i)
    {
      printf("Input A[%d]: ", i);
      scanf("%d", A + i);
    }
  }

  if (selection == 1 || selection == 2)
  {
    begin = clock();
    numInversions = getNumInversionsBruteForce(A, nA);
    end = clock();
    executionTime = (double)(end - begin);
    printf("\nExecution time for the brute force inversion counting algorithm: %f seconds\n", executionTime/CLOCKS_PER_SEC);
    printf("\nNumber of inversions: %d\n", numInversions);
  }
  else if (selection == 3 || selection == 4)
  {
    begin = clock();
    numInversions2 = 0;
    numInversions2 = getNumInversionsDivideAndConquer(A, nA);
    end = clock();
    executionTime = (double)(end - begin);
    printf("\nExecution time for the divide and conquer inversion counting algorithm: %f seconds\n", executionTime/CLOCKS_PER_SEC);
    printf("\nNumber of inversions (Divide and Conquer): %d\n", numInversions2);
  }


  /* --------------- Convex Hull Brute Force --------------- */

  if (selection == 5 || selection == 7)
  {
    S = (float**)malloc(2 * sizeof(float*));
    i = 0;
    fp = fopen(argv[1], "rb");
    if (fp == NULL)
    {
        printf("Please enter a valid file name when executing the program and chosing this option\n");
        return 0;
    }

    while (!feof (fp))
    {
      i += 1;
      S = (float**)realloc(S, 2 * i * sizeof(float*));
      *(S+i-1) = (float*)malloc(2 * sizeof(float));
      fscanf(fp, "%f %f \n", *(S+i-1), *(S+i-1)+1);
      /*printf("%.1f, %.1f\n",*(*(S+i-1)), *(*(S+i-1)+1));*/
    }

    nS = i;
    fclose(fp);
  }

  else if (selection == 6 || selection == 8)
  {
    printf("Enter number of points for set S: ");
    scanf("%d", &nS);
    printf("\n");

    S = (float**)malloc(nS * sizeof(float*));
    for (i=0; i<nS; i++)
    {
      *(S+i) = (float*)malloc(2 * sizeof(float));
      printf("Input x%d: ", i);
      scanf("%f", *(S+i));
      printf("Input y%d: ", i);
      scanf("%f", *(S+i)+1);
    }
  }

  if (selection == 5 || selection == 6)
  {
    begin = clock();
    convexHull = getConvexHullBruteForce(S, nS);
    end = clock();
    executionTime = (double)(end - begin);
    printf("\nExecution time for the brute force convex hull algorithm: %f seconds\n", executionTime/CLOCKS_PER_SEC);
  }

  else if (selection == 7 || selection == 8)
  {
    begin = clock();
    convexHull = conqerConvexHull(S, nS);
    end = clock();
    executionTime = (double)(end - begin);
    printf("\nExecution time for the divide and conquer convex hull algorithm: %f seconds\n", executionTime/CLOCKS_PER_SEC);
  }
  if (selection == 5 || selection == 6 || selection == 7 || selection == 8)
  {
    numExtreme = (int)*(*(convexHull));
    printf("\nNumber of points on the convex hull: %d", numExtreme);
    printf("\n\nThe following is the convex hull:\n\n");
    for (i = 1; i < numExtreme+1; i++)
    {
      printf("Point x%d: %.1f, y%d: %.1f\n", i, *(*(convexHull+i)), i, *(*(convexHull+i)+1));
    }
  }

  return 0;
}
