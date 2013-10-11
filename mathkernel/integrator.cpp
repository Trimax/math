/*           FILE: integrator.cpp
 *           DATE: 18 Sep 2010 ã.
 *         AUTHOR: Eliseev Dmitry
 *        PROJECT: mathkernel
 *    LAST UPDATE: Updated on 18.09.2010
 *           NOTE: Definite integrator class implementation
 *
 * CONTACT PERSON: Eliseev Dmitry
 */

/* System modules including */
#include <math.h>

/* Engine modules including */

/* Project modules including */
#include "integrator.h"
#include "timer.h"

/***
 * Definitions and constants
 ***/

unsigned int Integrator::numIterations = 0;
unsigned long Integrator::numSeconds = 0;

/***
 * Functions definition
 ***/

/***
 * FUNCTION: Integrates equation using left-rectangles method
 *   RETURN: Definite integral of equation
 *    PARAM: [IN] equation   - equation to integrate
 *    PARAM: [IN] start      - left integration border
 *    PARAM: [IN] end        - right integration border
 *    PARAM: [IN] precission - precission
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
double Integrator::Rectangles( const Equation &equation, const double start, const double end, const double precission )
{
  /* Integral value */
  double integralValue = 0.0, prevIntegralValue = 0.0;

  /* According to Runge rule */
  const double theta =  1.0 / 3.0;

  /* Number of intervals */
  unsigned int numOfIntervals = 2, k = 0;

  /* Values array */
  double *values = NULL;

  /* Interval size */
  double width = 0.0;

  /* Timer creation */
  Timer timer;

  /* While precission will not be achieved */
  numIterations = 0;
  do 
  {
    if (!values)
    {
      values = new double[numOfIntervals];
      width = (end - start) / 2.0;
      values[0] = equation(start);
      values[1] = equation(start + width);
    }
    else
    {
      double *newValues = new double[numOfIntervals * 2];
      memset(newValues, 0, 2 * sizeof(double) * numOfIntervals);

      /* Decrease interval width */
      width /= 2;

      /* Copying new values */
      for (k = 0; k < numOfIntervals; k++)
      {
        newValues[2 * k]     = values[k];
        newValues[2 * k + 1] = equation(start + width * (2 * k + 1));
      }   

      /* Delete old values array and replace it with newly created */
      delete[] values;
      values = newValues;
      numOfIntervals *= 2;
    }

    /* Recalculate integral value */
    prevIntegralValue = integralValue;
    integralValue = 0.0;
    for (k = 0; k < numOfIntervals; k++)
      integralValue += width * values[k];

    /* Increase number of iterations */
    numIterations++;
  } while (theta * fabs(integralValue - prevIntegralValue) > precission);

  /* That's it */
  delete[] values;

  /* Determine equation time */
  numSeconds = timer.GetTimePassed();

  /* That's it */ 
  return integralValue;
} /* End of 'Integrator::Rectangles' method */

/***
 * FUNCTION: Integrates equation using Simpson method
 *   RETURN: Definite integral of equation
 *    PARAM: [IN] equation   - equation to integrate
 *    PARAM: [IN] start      - left integration border
 *    PARAM: [IN] end        - right integration border
 *    PARAM: [IN] precission - precission
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
double Integrator::Simpson( const Equation &equation, const double start, const double end, const double precission )
{
  /* Integral value */
  double integralValue = 0.0, prevIntegralValue = 0.0;

  /* According to Runge rule */
  const double theta =  1.0 / 15.0;

  /* Number of intervals */
  unsigned int numOfIntervals = 1, k = 0;
  unsigned int numOfValues = 2 * numOfIntervals + 1;

  /* Values array */
  double *values = NULL;

  /* Interval size */
  double width = (end - start) / 2.0;

  /* Timer creation */
  Timer timer;

  /* While precission will not be achieved */
  numIterations = 0;
  do 
  {
    if (!values)
    {
      values = new double[numOfValues];
      values[0] = equation(start);
      values[1] = equation((start + end) / 2.0);
      values[2] = equation(end);      
    }
    else
    {
      unsigned int newNumIntervals = numOfIntervals * 2;
      double *newValues = new double[2 * newNumIntervals + 1];
      memset(newValues, 0, (2 * newNumIntervals + 1) * sizeof(double));

      /* Decrease interval width */
      width /= 2;

      /* Copying old values */
      for (k = 0; k < numOfValues; k++)
        newValues[2 * k] = values[k];

      /* Calculate new values */
      for (k = 0; k < numOfValues - 1; k++)
        newValues[2 * k + 1] = equation(start + width * (2 * k + 1));

      /* Delete old values array and replace it with newly created */
      delete[] values;
      values = newValues;
      
      /* Recalculate number of values & intervals */
      numOfIntervals = newNumIntervals;
      numOfValues = 2 * numOfIntervals + 1;
    }

    /* Recalculate integral value */
    prevIntegralValue = integralValue;
    integralValue = values[0] + values[2 * numOfIntervals];

    /* Determine sum */
    for (k = 1; k <= numOfIntervals; k++)
      integralValue += 4 * values[2 * k - 1];
    for (k = 1; k <= numOfIntervals - 1; k++)
      integralValue += 2 * values[2 * k];

    /* Last division */
    integralValue *= (end - start) / (6.0 * numOfIntervals);

    /* Increase number of iterations */
    numIterations++;
  } while (theta * fabs(integralValue - prevIntegralValue) > precission);

  /* That's it */
  delete[] values;

  /* Determine spent time */
  numSeconds = timer.GetTimePassed();

  /* That's it */ 
  return integralValue;
} /* End of 'Integrator::Simpson' method */

/***
 * FUNCTION: Determine number of iterations of last integration
 *   RETURN: Number of iterations
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
unsigned int Integrator::GetNumIterations( void )
{
  return numIterations;
} /* End of 'Integrator::GetNumIterations' method */

/***
 * FUNCTION: Determine time, spent during last integration
 *   RETURN: Time, spent during last integration (in seconds)
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
unsigned int Integrator::GetSpentTime( void )
{
  return numSeconds;
} /* End of Integrator::GetSpentTime'' method */