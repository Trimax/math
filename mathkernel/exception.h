#ifndef __EXCEPTION_H__633624057850442500
#define __EXCEPTION_H__633624057850442500

/*           FILE: veexception.h
 *           DATE: 16 Nov 2008 ã.
 *         AUTHOR: Eliseev Dmitry
 *        PROJECT: Venta
 *    LAST UPDATE: Updated on 16.11.2008
 *           NOTE: Exception class definition
 *
 * CONTACT PERSON: Eliseev Dmitry
 */

/* System modules including */
#include <string>

/* Project modules including */
#include "constants.h"

/* Sharing namespace */
using namespace std;

/***
 * Definitions and constants
 ***/

/* Classes definition */
class DllExport Exception 
{
  char *message;
public:

  /***
   * FUNCTION: Exception class constructor
   *    PARAM: [IN] msg - exception message
   *   AUTHOR: Eliseev Dmitry
   ***/
  Exception( const string msg = "" );

  /***
   * FUNCTION: Exception class copy constructor
   *    PARAM: [IN] s - source exception
   *   AUTHOR: Eliseev Dmitry
   ***/
  Exception( const Exception &s );

  /***
   * FUNCTION: Exception class destructor
   *   AUTHOR: Eliseev Dmitry
   ***/
  ~Exception( void );

  /***
   * FUNCTION: Requests exception message
   *   RETURN: Message
   *   AUTHOR: Eliseev Dmitry
   ***/
  const char* GetMessage( void ) const;
}; /* End of 'Exception' class */

#endif /* __EXCEPTION_H__633624057850442500 */
