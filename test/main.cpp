/*           FILE: main.cpp
 *           DATE: 18 Sep 2010 ã.
 *         AUTHOR: Eliseev Dmitry
 *        PROJECT: test
 *    LAST UPDATE: Updated on 18.09.2010
 *           NOTE: Main project file
 *
 * CONTACT PERSON: Eliseev Dmitry
 */

/* System modules including */
#include <iostream>
#include <conio.h>

/* Engine modules including */

/* Project modules including */
#define MATHKERNEL_IMPORT
#include "../mathkernel/integrator.h"

/***
 * Definitions and constants
 ***/

/***
 * Functions definition
 ***/

/***
 * FUNCTION: Main program function
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
void main( void )
{
  try
  {
    /* Loading equation */
    Equation f("");
    f.LoadFromFile("equation.txt");

    /* Making integration */
    Equation result = ParametricIntegrator::Rectangles(f, 0.0, 5.0, 5);

    /* Output result */
    result.SaveToFile("output.txt");
    cout << "Calculation finished" << endl;
  }
  catch (Exception e)
  {
    cout << "Exception occurred: " << e.GetMessage() << endl;
  }

  /* Waiting for a key */
  getch();
} /* End of 'main' function */
