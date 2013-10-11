/*           FILE: timer.cpp
 *           DATE: 28 Sep 2010 ã.
 *         AUTHOR: Eliseev Dmitry
 *        PROJECT: mathkernel
 *    LAST UPDATE: Updated on 28.09.2010
 *           NOTE: write here
 *
 * CONTACT PERSON: Eliseev Dmitry
 */

/* System modules including */
#include <time.h>

/* Engine modules including */

/* Project modules including */
#include "timer.h"

/***
 * Definitions and constants
 ***/

/***
 * Functions definition
 ***/

/***
 * FUNCTION: Class constructor
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
Timer::Timer( void )
{
  time_t t;
  time(&t);
  timerCreated = (unsigned long)t;
} /* End of 'Timer::Timer' method */

/***
 * FUNCTION: Class destructor
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
Timer::~Timer( void )
{

} /* End of 'Timer::~Timer' method */

/***
 * FUNCTION: Gets time in seconds after timer creation
 *   RETURN: Number of seconds since timer was created
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
unsigned long Timer::GetTimePassed( void ) const
{
  time_t t;
  time(&t);

  /* Number of seconds since timer was created */
  return (unsigned long)(t - timerCreated);
} /* End of 'Timer::GetTimePassed' method */

