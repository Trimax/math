#ifndef __INTEGRATOR_H__634204501781562500
#define __INTEGRATOR_H__634204501781562500

/*           FILE: integrator.h
 *           DATE: 18 Sep 2010 ã.
 *         AUTHOR: Eliseev Dmitry
 *        PROJECT: mathkernel
 *    LAST UPDATE: Updated on 18.09.2010
 *           NOTE: Integrator class definition
 *
 * CONTACT PERSON: Eliseev Dmitry
 */

/* System modules including */

/* Engine modules including */

/* Project modules including */
#include "equation.h"

/***
 * Definitions and constants
 ***/

/* Definite integration of functions without parameters */
class DllExport Integrator
{
  static unsigned int numIterations;
  static unsigned long numSeconds;
public:
  /* Default precission for calculation */
  static const double c_DefaultPrecission;

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
  static double Rectangles( const Equation &equation, 
                            const double start, const double end, 
                            const double precission = Integrator::c_DefaultPrecission );

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
  static double Simpson( const Equation &equation, 
                         const double start, const double end, 
                         const double precission = Integrator::c_DefaultPrecission );

  /***
   * FUNCTION: Determine number of iterations of last integration
   *   RETURN: Number of iterations
   *      SEE: write me
   *   AUTHOR: Eliseev Dmitry
   ***/
  static unsigned int GetNumIterations( void );

  /***
   * FUNCTION: Determine time, spent during last integration
   *   RETURN: Time, spent during last integration (in seconds)
   *      SEE: write me
   *   AUTHOR: Eliseev Dmitry
   ***/
  static unsigned int GetSpentTime( void );
}; /* End of 'Integrator' class */

/* Definite integration of functions with parameters */
class DllExport ParametricIntegrator
{
  static unsigned long numSeconds;
public:
  /* Default precission for calculation */
  static const unsigned int c_DefaultNumIterations;
  
  /***
   * FUNCTION: Integrates equation using center-rectangles method
   *   RETURN: Finite sum depends on parameters
   *    PARAM: [IN] equation      - equation to integrate
   *    PARAM: [IN] start         - left integration border
   *    PARAM: [IN] end           - right integration border
   *    PARAM: [IN] numIterations - number of iterations
   *      SEE: write me
   *   AUTHOR: Eliseev Dmitry
   ***/
  static Equation Rectangles( const Equation &equation, 
                              const double start, const double end, 
                              const unsigned int numIterations = ParametricIntegrator::c_DefaultNumIterations);

  /***
   * FUNCTION: Integrates equation using Simpson method
   *   RETURN: Finite sum depends on parameters
   *    PARAM: [IN] equation      - equation to integrate
   *    PARAM: [IN] start         - left integration border
   *    PARAM: [IN] end           - right integration border
   *    PARAM: [IN] numIterations - number of iterations
   *      SEE: write me
   *   AUTHOR: Eliseev Dmitry
   ***/
  static Equation Simpson( const Equation &equation, 
                           const double start, const double end, 
                           const unsigned int numIterations = ParametricIntegrator::c_DefaultNumIterations );

  /***
   * FUNCTION: Determine time, spent during last integration
   *   RETURN: Time, spent during last integration (in seconds)
   *      SEE: write me
   *   AUTHOR: Eliseev Dmitry
   ***/
  static unsigned int GetSpentTime( void );
}; /* End of 'Integrator' class */

#endif /* __INTEGRATOR_H__634204501781562500 */
