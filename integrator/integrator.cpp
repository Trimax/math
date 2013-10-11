/*           FILE: integrator.cpp
 *           DATE: 25 Sep 2010 ã.
 *         AUTHOR: Eliseev Dmitry
 *        PROJECT: integrator
 *    LAST UPDATE: Updated on 24.09.2010
 *           NOTE: write here
 *
 * CONTACT PERSON: Eliseev Dmitry
 */

/* System modules including */
#include <iostream>
#include <fstream>

/* Engine modules including */

/* Project modules including */
#include "../mathkernel/integrator.h"

/***
 * Definitions and constants
 ***/

/***
 * Functions definition
 ***/

/***
 * FUNCTION: Main program function
 *   RETURN: Always 0
 *    PARAM: [IN] argc - number of CL arguments
 *    PARAM: [IN] argv - CL arguments array
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
int main( const int argc, const char *argv[] )
{
  /* Number of arguments */
  if (argc < 5)
  {
    cout << "error=Empty either equation or bounds or precision or method" << endl;
    return 0;
  }

  /* Reading expression */
  string expr;
  ifstream f(argv[1]);
  getline(f, expr);
  f.close();

  /* Remove file */
  string fullName(argv[1]);
  string fName = fullName.substr(fullName.find_last_of('\\') + 1); 
  unlink(fName.c_str());

  /* Transform to strings */
  string method     = string(argv[2]);

  /* Try to calculate */
  try
  {
    Equation equation(expr);
 
    /* Integration */
    if (method == "rect")
    {
      double result = Integrator::Rectangles(equation, atof(argv[3]), atof(argv[4]), atof(argv[5]));
      cout << "result=" << result << ";" << Integrator::GetNumIterations() << endl;

    } else if (method == "simp")
    {
      double result = Integrator::Simpson(equation, atof(argv[3]), atof(argv[4]), atof(argv[5]));
      cout << "result=" << result << ";" << Integrator::GetNumIterations() << endl;
    } else
      throw Exception("Unknown method");
  }
  catch (Exception e)
  {
    cout << "error=" << e.GetMessage() << endl;  	
  }  

  /* That's it */
  return 0;
} /* End of 'main' function */
