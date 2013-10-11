/*           FILE: wrapper.cpp
 *           DATE: 20 Sep 2010 ã.
 *         AUTHOR: Math kernel library wrapper for C#
 *        PROJECT: wrapper
 *    LAST UPDATE: Updated on 20.09.2010
 *           NOTE: write here
 *
 * CONTACT PERSON: Eliseev Dmitry
 */

/* System modules including */
#include <windows.h>
#include <string>

/* Engine modules including */

/* Project modules including */
#include "wrapper.h"
#include "../mathkernel/integrator.h"

/***
 * Definitions and constants
 ***/

/***
 * Functions definition
 ***/

BOOL __stdcall DllMain(HINSTANCE hInst, DWORD dwReason, LPVOID lpReserved) {
  return  TRUE;
}

/***
 * FUNCTION: Integrates equation using Simpson method
 *   RETURN: Integration result
 *    PARAM: [IN] equation   - equation's string representation
 *    PARAM: [IN] from       - left border of integration interval
 *    PARAM: [IN] to         - right border of integration interval
 *    PARAM: [IN] precision - integration precision
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
extern "C" DllExport void __stdcall Integrate( struct Expression *expr )
{
  std::string s = string(expr->expression);
  expr->err = 0;
  
  try
  {
    Equation eq(s);
    expr->r = Integrator::Simpson(eq, expr->s, expr->f, expr->p);
  }
  catch (Exception e)
  {
    expr->err = 1;
  }
} /* End of 'Integrate' function */

extern "C" DllExport void __stdcall Sample( int a )
{
  a = a + 1;
}