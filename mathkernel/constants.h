#ifndef __CONSTANTS_H__634204150468437500
#define __CONSTANTS_H__634204150468437500

/*           FILE: constants.h
 *           DATE: 18 Sep 2010 ã.
 *         AUTHOR: Eliseev Dmitry
 *        PROJECT: mathkernel
 *    LAST UPDATE: Updated on 18.09.2010
 *           NOTE: Constants class definition
 *
 * CONTACT PERSON: Eliseev Dmitry
 */

/* System modules including */

/* Engine modules including */

/* Project modules including */

/***
 * Definitions and constants
 ***/

#ifndef MATHKERNEL_IMPORT
#define DllExport __declspec( dllexport )
#define TEST_API __declspec(dllexport)
#else
#define DllExport __declspec( dllexport )
#pragma message("Automatic library linking")
#endif

/* Classes definition */
class DllExport Constants
{
public:
  /* Math constants */
  const static double INFINITY;
  const static double PI;
  const static double E;

  /* Physics constants */
}; /* End of 'Constants' class */

#endif /* __CONSTANTS_H__634204150468437500 */
