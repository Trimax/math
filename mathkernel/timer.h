#ifndef __TIMER_H__634213061531562500
#define __TIMER_H__634213061531562500

/*           FILE: timer.h
 *           DATE: 28 Sep 2010 ã.
 *         AUTHOR: Eliseev Dmitry
 *        PROJECT: mathkernel
 *    LAST UPDATE: Updated on 28.09.2010
 *           NOTE: Timer class definition
 *
 * CONTACT PERSON: Eliseev Dmitry
 */

/* System modules including */

/* Engine modules including */

/* Project modules including */

/***
 * Definitions and constants
 ***/

/* Classes definition */
class Timer 
{
  unsigned long timerCreated;
public:
  /***
   * FUNCTION: Class constructor
   *      SEE: write me
   *   AUTHOR: Eliseev Dmitry
   ***/
  Timer( void );

  /***
   * FUNCTION: Class destructor
   *      SEE: write me
   *   AUTHOR: Eliseev Dmitry
   ***/
  ~Timer( void );

  /***
   * FUNCTION: Gets time in seconds after timer creation
   *   RETURN: Number of seconds since timer was created
   *      SEE: write me
   *   AUTHOR: Eliseev Dmitry
   ***/
  unsigned long GetTimePassed( void ) const;
}; /* End of 'Timer' class */

#endif /* __TIMER_H__634213061531562500 */
