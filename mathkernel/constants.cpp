/*           FILE: constants.cpp
 *           DATE: 18 Sep 2010 ã.
 *         AUTHOR: Eliseev Dmitry
 *        PROJECT: mathkernel
 *    LAST UPDATE: Updated on 18.09.2010
 *           NOTE: Constants class implementation
 *
 * CONTACT PERSON: Eliseev Dmitry
 */

/* System modules including */
#define _USE_MATH_DEFINES
#include <math.h>

/* Engine modules including */

/* Project modules including */
#include "constants.h"
#include "integrator.h"

/***
 * Definitions and constants
 ***/

/*** Math constants ***/
const double Constants::E        = M_E;
const double Constants::PI       = M_PI;
const double Constants::INFINITY = 10e307;

/*** Physics constants ***/

/*** Integrators constants ***/
const double Integrator::c_DefaultPrecission = 10e-5;
const unsigned int ParametricIntegrator::c_DefaultNumIterations = 100;


