/*           FILE: calculator.cpp
 *           DATE: 24 Sep 2010 ã.
 *         AUTHOR: Eliseev Dmitry
 *        PROJECT: calculator
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
  if (argc < 3)
  {
    cout << "error=Empty either equation or variable value" << endl;
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
  string var  = string(argv[2]);  

  /* Try to calculate */
  try
  {
    Equation equation(expr);
    double result = equation(atof(argv[2]));
    cout << "result=" << result << endl;
  }
  catch (Exception e)
  {
    cout << "error=" << e.GetMessage() << endl;  	
  }  

  /* That's it */
  return 0;
} /* End of 'main' function */
