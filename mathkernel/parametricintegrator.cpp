/*           FILE: parametricintegrator.cpp
 *           DATE: 18 Sep 2010 ã.
 *         AUTHOR: Eliseev Dmitry
 *        PROJECT: mathkernel
 *    LAST UPDATE: Updated on 18.09.2010
 *           NOTE: Parametric integrator class implementation
 *
 * CONTACT PERSON: Eliseev Dmitry
 */

/* System modules including */

/* Engine modules including */

/* Project modules including */
#include "integrator.h"
#include "timer.h"

/***
 * Definitions and constants
 ***/

unsigned long ParametricIntegrator::numSeconds = 0;

/***
 * Functions definition
 ***/

/***
 * FUNCTION: Integrates equation using center-rectangles method
 *   RETURN: Definite integral of equation
 *    PARAM: [IN] equation      - equation to integrate
 *    PARAM: [IN] start         - left integration border
 *    PARAM: [IN] end           - right integration border
 *    PARAM: [IN] numIterations - number of iterations
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
Equation ParametricIntegrator::Rectangles( const Equation &equation, const double start, const double end, const unsigned int numIterations )
{
  double step = (end - start) / numIterations;
  unsigned int i = 0;

  /* Result equation */
  Equation result("0");
  Equation width(step);

  /* Timer creation */
  Timer timer;

  /* For each iteration */
  for (i = 0; i < numIterations; i++)
    result += width * equation.GetEquation(step * i);

  /* That's it */
  result.Simplify();

  /* Determine spent time */
  numSeconds = timer.GetTimePassed();
  return result;
} /* End of 'Integrator::Rectangles' method */

/***
 * FUNCTION: Integrates equation using Simpson method
 *   RETURN: Definite integral of equation
 *    PARAM: [IN] equation      - equation to integrate
 *    PARAM: [IN] start         - left integration border
 *    PARAM: [IN] end           - right integration border
 *    PARAM: [IN] numIterations - number of iterations
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
Equation ParametricIntegrator::Simpson( const Equation &equation, const double start, const double end, const unsigned int numIterations )
{
  unsigned int i = 0;

  /* Timer creation */
  Timer timer;

  /* Result equation */
  Equation result = Equation(start) + Equation(end);

  /* Odd members */
  Equation oddResult("0");
  for (i = 1; i <= 2 * numIterations - 1; i+=2)
    oddResult += equation.GetEquation(start + (end - start) * i / (2 * numIterations));

  /* Even members */
  Equation evenResult("0");
  for (i = 2; i <= 2 * numIterations - 2; i+=2)
    evenResult += equation.GetEquation(start + (end - start) * i / (2 * numIterations));

  /* Add calculated values */
  result += Equation("4") * oddResult + Equation("2") * evenResult;

  /* That's it */
  result *= Equation((end - start) / (6 * numIterations));
  result.Simplify();

  /* Determine spent time */
  numSeconds = timer.GetTimePassed();
  return result;
} /* End of 'Integrator::Simpson' method */

/***
 * FUNCTION: Determine time, spent during last integration
 *   RETURN: Time, spent during last integration (in seconds)
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
unsigned int ParametricIntegrator::GetSpentTime( void )
{
  return numSeconds;
} /* End of ParametricIntegrator::GetSpentTime'' method */