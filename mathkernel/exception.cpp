/*           FILE: exception.cpp
 *           DATE: 17 Nov 2008 ã.
 *         AUTHOR: Eliseev Dmitry
 *        PROJECT: Venta
 *    LAST UPDATE: Updated on 17.11.2008
 *           NOTE: Exception class implementation
 *
 * CONTACT PERSON: Eliseev Dmitry
 */

/* System modules including */
#include <stdlib.h>

/* Engine modules including */

/* Project modules including */
#include "exception.h"

/***
 * Definitions and constants
 ***/

/***
 * Functions definition
 ***/

/***
 * FUNCTION: Exception class constructor
 *    PARAM: [IN] msg - exception message
 *   AUTHOR: Eliseev Dmitry
 ***/
Exception::Exception( const string msg )
{
  message = new char[msg.length() + 1];

  /* Storing message */
  memset(message, 0, msg.length() + 1);
  memcpy(message, msg.c_str(), msg.length());
} /* End of 'Exception::Exception' function */

/***
 * FUNCTION: Exception class copy constructor
 *    PARAM: [IN] s - source exception
 *   AUTHOR: Eliseev Dmitry
 ***/
Exception::Exception( const Exception &s )
{
  message = new char[strlen(s.message) + 1];
  memset(message, 0, strlen(s.message) + 1);
  memcpy(message, s.message, strlen(s.message));
} /* End of 'Exception::Exception' method */

/***
 * FUNCTION: Exception class destructor
 *   AUTHOR: Eliseev Dmitry
 ***/
Exception::~Exception( void )
{
  delete[] message;
} /* End of 'Exception::~Exception' method */

/***
 * FUNCTION: Requests exception message
 *   RETURN: Message
 *   AUTHOR: Eliseev Dmitry
 ***/
const char* Exception::GetMessage( void ) const
{
  return message;
} /* End of 'Exception::GetMessage' function */
