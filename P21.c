/* Name: Thomas Green
 * ID: 1048389
 * Assignment #: 2
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


float** getConvexHullBruteForce(float **S, int n);
void sortConvexHull(float **convexHull, int numExtreme);


/* Computes the convex hull using a brute force algorithm
 * @param S: the set of 2d points
 * @param n: the size of S
 * @return the pointer to the convex hull that get's created
 */
float** getConvexHullBruteForce(float **S, int n) {

  float **convexHull;

  /* p1 and p2 make up the reference line with which p3 get's compared to */
  float x1;
  float x2;
  float x3;
  float y1;
  float y2;
  float y3;

  /* Loop incrementers */
  int i; /* Used to iterate through p1 values                   */
  int j; /* Used to iterate through p2 values                   */
  int k; /* Used to iterate through p3 values                   */
  int l; /* Used to iterate through extreme points found so far */

  float a;  /* y2 - y1         */
  float b;  /* x1 - x2         */
  float c;  /* c = x1y2 - y1x2 */
  float d;  /* d = ax+by-c     */

  int comparison;          /* Used to decipher whether p1 and p2 are extreme points          */
  float numExtreme;          /* Keeps track of the number of extreme points                    */
  bool isFirstComparison;  /* Is this the first point that is being compared to (p1, p2)?    */
  bool firstSide;          /* The sign of d for the first point that is compared to (p1, p2) */
  bool side;               /* The sign of d for a given comparison                           */
  bool isExtreme;          /* Asserts whether (p1, p2) are extreme points                    */
  bool isPoint1New;
  bool isPoint2New;


  convexHull = (float**)malloc(2*sizeof(float*));
  *(convexHull) = (float*)malloc(sizeof(float));  /* Reserve the first element for the number of extreme points */
  numExtreme = 0;

  /* i represents p1 and j represents p2           */
  /* Iterates through each combination of (p1, p2) */
  for (i = 0; i < n-1; i++)
  {
    for (j = i+1; j < n; j++)
    {

      /* define p1 and p2 for this iteration */
      x1 = *(*(S+i));
      x2 = *(*(S+j));
      y1 = *(*(S+i)+1);
      y2 = *(*(S+j)+1);

      /* Define a, b, and c for this iteration */
      a = y2 - y1;
      b = x1 - x2;
      c = x1*y2 - y1*x2;

      k = 0;
      isFirstComparison = true;
      isExtreme = true;
      comparison = 0;

      /* k represents p3                                                            */
      /* Compare which side each point (p3) is with refference to the line (p1, p2) */
      while (k < n && isExtreme == true)
      {
        /* If the point is not one of the points defining the line */

        if ((k != j) && (k != i))
        {
          /* Define p3 */
          x3 = *(*(S+k));
          y3 = *(*(S+k)+1);

          /* Determine d */
          d = a*x3 + b*y3 - c;


          /* If this is the first comparison between p3 and (p1, p2),               */
          /* Then take note of which side p3 is wrt (p1, p2)                        */
          /* And keep track how how many other points p3 that are on this same side */
          if (isFirstComparison == true)
          {
            if (d<0)
            {
              firstSide = false;
            }
            if (d>0)
            {
              firstSide = true;
            }
            isFirstComparison = false;
          }

          if (d<0)
          {
            side = false;
          }
          else if (d>0)
          {
            side = true;
          }
          else /*If the point is colinear with (p1, p2), it is still part of the convex hull */
          {
            side = firstSide;
          }

          /* 2 points (p3) lie on opposide sides wrt line (p1, p2)  */
          /* p1 and p2 are not extreme points                       */
          if (side != firstSide)
          {
            isExtreme = false;
          }
          else
          {
            comparison++;
          }
        }
        k++;
      }

      /* If n-2 points lie on the same side with respect to (p1, p2) */
      /* Then p1 and p2 are extreme points */
      if (comparison == n-2)
      {
        /*printf("An extreme pair: x1: %f, y1: %f, x2: %f, y2: %f\n",
        x1, y1, x2, y2);*/

        /* p1 and p2 are assumed to be new extreme points to begin with */
        isPoint1New = true;
        isPoint2New = true;

        /* Iterate through all extreme points that have been found so far */
        for (l = 1; l < numExtreme+1; l++)
        {
          x3 = *(*(convexHull+l));
          y3 = *(*(convexHull+l)+1);

          /* If p1 has been found already */
          if (x1 == x3 && y1 == y3)
          {
            isPoint1New = false;
          }

          /* If p2 has been found already */
          if (x2 == x3 && y2 == y3)
          {
            isPoint2New = false;
          }
        }

        /* If p1 is found to be a new extreme point, add it to convex hull */
        if (isPoint1New == true)
        {
          numExtreme++;
          convexHull = (float**)realloc(convexHull, (numExtreme+1) * sizeof(float*));
          *(convexHull+(int)numExtreme) = (float*)malloc(2 * sizeof(float));
          *(convexHull+(int)numExtreme) = *(S+i);
        }

        /* If p2 is found to be a new extreme point, add it to convex hull */
        if (isPoint2New == true)
        {
          numExtreme++;
          convexHull = (float**)realloc(convexHull, (numExtreme+1) * sizeof(float*));
          *(convexHull+(int)numExtreme) = (float*)malloc(2 * sizeof(float));
          *(convexHull+(int)numExtreme) = *(S+j);
        }
      }
    }
  }

  /* Sort convex hull points in the order of ascending x values */
  sortConvexHull(convexHull, numExtreme);

  /* Insert the number of extreme points in convex hull such that it can be accessed later */
  *(*(convexHull)) = numExtreme;

  return convexHull;
}


/* Sorts the final convex hull by their x coordinates
 * @param convexHull: the convex hull to be sorted
 * @param numExtreme: the number of extreme points in the convex hull
 */
void sortConvexHull(float **convexHull, int numExtreme) {

  int i;
  int j;
  int min;
  float *temp;

  for (i = 1; i < numExtreme; i++)
  {
    min = i;
    for (j = i+1; j < numExtreme+1; j++)
    {
      if (*(*(convexHull+j)) < *(*(convexHull+min)))
      {
        min = j;
      }
    }
    temp = *(convexHull+i);
    *(convexHull+i) = *(convexHull+min);
    *(convexHull+min) = temp;
  }
}
