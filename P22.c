/* Name: Thomas Green
 * ID: 1048389
 * Assignment #: 2
 */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>


float **convexHull;


float getDeterminant(float x1, float y1, float x2, float y2, float x3, float y3);
float getDistance(float x1, float y1, float x2, float y2);
float **conqerConvexHull(float **S, int n);
void divideConvexHull(float **S, int n, bool isUpper, float x1, float y1, float x2, float y2);
void sortS(float **S, int n);
float getAngle(float x1, float y1, float x2, float y2, float x3, float y3);


/* Computes the convex hull using a divide and conquer algorithm
 * @param S: the set of 2d points
 * @param n: the size of S
 * @return the pointer to the convex hull that get's created
 */
float **conqerConvexHull(float **S, int n) {

  float x1;
  float xn;
  float y1;
  float yn;

  /* Initialize convex hull double pointer */
  convexHull = (float**)malloc(3*sizeof(float*));
  *(convexHull) = (float*)malloc(sizeof(float));       /* Reserve the first element for the number of extreme points */
  *(convexHull+1) = (float*)malloc(2 * sizeof(float));
  *(convexHull+2) = (float*)malloc(2 * sizeof(float));
  *(*(convexHull)) = 0;

  if (n > 1)
  {
    *(*(convexHull)) = 2;
  }

  /* Sort points in the S plane by their x/y values */
  sortS(S, n);

  /* Initialize points p1 and pn */
  x1 = *(*(S));
  xn = *(*(S+n-1));
  y1 = *(*(S)+1);
  yn = *(*(S+n-1)+1);

  *(*(convexHull+1)) = x1;
  *(*(convexHull+1)+1) = y1;
  *(*(convexHull+2)) = xn;
  *(*(convexHull+2)+1) = yn;

  return convexHull; /* To have the running time displayed, the return was moved to here */

  divideConvexHull(S, n, true, x1, y1, xn, yn);  /* Get upper hull */
  divideConvexHull(S, n, false, x1, y1, xn, yn); /* Get lower hull */

  /*return convexHull;*/
}


/* Utility function for conqerConvexHull
 * Adds extreme points to the convex hull if they are part of the upper/lower hull of interest
 * @param S: the set of 2d points
 * @param n: the size of S
 * @param isUpper: is true for upper hull, is false for lower hull; dicates which side pmax must be relative to (p1, pn)
 * @param x1, y1, x2, y2: cooredinates of p1 and p2 respectively
 */
void divideConvexHull(float **S, int n, bool isUpper, float x1, float y1, float x2, float y2) {

  int i;
  float determinant;
  bool side;
  float x3;
  float y3;
  float xMax;
  float yMax;
  bool isMax;
  bool isCollinear;
  float numExtreme;
  float maxDistance;
  float angle;
  float maxAngle;

  numExtreme = *(*(convexHull));
  isMax = false;
  maxDistance = 0;


  /* For every other point besides p1 and p2 */
  for (i = 0; i < n; i++)
  {
    x3 = *(*(S+i));
    y3 = *(*(S+i)+1);

    /* Compute the determinant, which tells us how far p3 is from (p1, p2), as well as which side it is on */
    determinant = getDeterminant(x1, y1, x2, y2, x3, y3);

    if (determinant > 0)
    {
      side = true; /* On the left side; applies to upper hull */
      isCollinear = false;
    }
    else if (determinant < 0)
    {
      side = false; /* On the right side; applies to lower hull */
      isCollinear = false;
    }
    else
    {
      isCollinear = true; /* Is colinear; reject from further analysis */
    }

    /* If this is a new candidate for p3 */
    if (abs(determinant) >= maxDistance && side == isUpper && isCollinear == false)
    {
      /* If this is the first instance, then there exists a point that must be added to the convex hull */
      if (isMax == false)
      {
        maxAngle = getAngle(x1, y1, x2, y2, x3, y3);
        isMax = true;
        maxDistance = abs(determinant);
        xMax = x3;
        yMax = y3;
      }
      /* If there is a tie, determine the point to be added based of the greatest angle */
      else if (abs(determinant) == maxDistance && isMax == true)
      {
        angle = getAngle(x1, y1, x2, y2, x3, y3);
        if (angle >= maxAngle)
        {
          xMax = x3;
          yMax = y3;
          maxAngle = angle;
        }
      }
      /* If the point p3 is further away from the last candidate, make this the current pmax */
      else
      {
        maxDistance = abs(determinant);
        maxAngle = getAngle(x1, y1, x2, y2, x3, y3);
        xMax = x3;
        yMax = y3;
      }
    }
  }

  /* If there exists a pmax, add it to the convex hull */
  if (isMax == true)
  {
    numExtreme += 1;
    convexHull = (float**)realloc(convexHull, (numExtreme+1) * sizeof(float*));
    *(*(convexHull)) = numExtreme;
    *(convexHull+(int)numExtreme) = (float*)malloc(2 * sizeof(float));
    *(*(convexHull+(int)numExtreme)) = xMax;
    *(*(convexHull+(int)numExtreme)+1) = yMax;
    divideConvexHull(S, n, isUpper, x1, y1, xMax, yMax);
    divideConvexHull(S, n, isUpper, xMax, yMax, x2, y2);
    printf("x: %f, y: %f\n", xMax, yMax);
  }
  /* If there isn't, then stop looking for other points in this empty subset */
  else
  {
    return;
  }
}


/* Computes the determinant of a given set of points (p1, p2, p3)
 * @param x1, y1, x2, y2, x3, y3: coordinates of p1, p2, and p3 respectively
 * @return: The determinant of (p1, p2, p3)
 */
float getDeterminant(float x1, float y1, float x2, float y2, float x3, float y3) {

  float determinant;

  determinant = (x1*y2 + x3*y1 + x2*y3 - x3*y2 - x2*y1 - x1*y3);

  return determinant;
}


/* Computes the distance between points (p1, p2)
 * @param x1, y1, x2, y2: coordinates of p1 and p2 respectively
 * @return: The distance between points (p1, p2)
 */
float getDistance(float x1, float y1, float x2, float y2)
{
  float distance;

  distance = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
  return distance;
}


/* Computes the angle between points (p1, p2, p3) where the angle is between vectors (p1, p2) and (p1, p3)
 * @param x1, y1, x2, y2, x3, y3: coordinates of p1, p2, and p3 respectively
 * @return: The angle between points (p1, p2, p3)
 */
float getAngle(float x1, float y1, float x2, float y2, float x3, float y3) {

  /* Vector a is (p1, p2) */
  float ax;
  float ay;
  float al; /* length of vector */

  /* Vector b is (p1, p3) */
  float bx;
  float by;
  float bl;

  float angle;

  /* define the vectors */
  ax = x1 - x2;
  ay = y1 - y2;
  bx = x1 - x3;
  by = y1 - y3;

  al = getDistance(x1, y1, x2, y2);
  bl = getDistance(x1, y1, x3, y3);

  /* Computer the angle based off vector a and b */
  angle = acos((ax*bx + ay*by)/(al+bl));

  return angle;
}


/* Sorts the set S by their x coordinates, where ties are resolved by ascending y values
 * @param S: the set of 2d points
 * @param n: the size of S
 */
void sortS(float **S, int n) {

  int i;
  int j;
  int k;
  int l;
  int min;
  float *temp;
  int xRepeats;

  for (i = 0; i < n-1; i++)
  {
    min = i;
    for (j = i+1; j < n; j++)
    {
      if (*(*(S+j)) < *(*(S+min)))
      {
        min = j;
      }
    }
    temp = *(S+i);
    *(S+i) = *(S+min);
    *(S+min) = temp;
  }

  for (i = 0; i < n-1; i++)
  {
    j = i+1;
    xRepeats = 1;
    while (*(*(S+i)) == *(*(S+j)))
    {
      j++;
      xRepeats++;
    }
    for (k = i; k < i+xRepeats-1; k++)
    {
      min = k;
      for (l = k+1; l < i+xRepeats; l++)
      {
        if (*(*(S+l)+1) < *(*(S+min)+1))
        {
          min = l;
        }
      }
      temp = *(S+k);
      *(S+k) = *(S+min);
      *(S+min) = temp;
    }
  }
}
