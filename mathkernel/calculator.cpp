/*           FILE: calculator.cpp
 *           DATE: 18 Sep 2010 ã.
 *         AUTHOR: Eliseev Dmitry
 *        PROJECT: mathkernel
 *    LAST UPDATE: Updated on 18.09.2010
 *           NOTE: Calculation method of equation class implementation
 *
 * CONTACT PERSON: Eliseev Dmitry
 */

/* System modules including */
#include <math.h>

/* Engine modules including */

/* Project modules including */
#include "equation.h"

/***
 * Definitions and constants
 ***/

/* Null value */
const double c_Null = 10e-307;

/***
 * Functions definition
 ***/

/***
 * FUNCTION: Compares double value with zero
 *   RETURN: True if value is about zero
 *    PARAM: [IN] v - value to compare
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
inline bool IsNull( const double v )
{
  if ((v < c_Null)&&(v > -c_Null))
    return true;
  return false;
} /* End of 'IsNull' function */

/***
 * FUNCTION: Hyperbolic sinus
 *   RETURN: Hyperbolic sinus
 *    PARAM: [IN] v - argument
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
double sh( const double v )
{
  return (exp(v) - exp(-v)) / 2.0;
} /* End of 'sh' function */

/***
 * FUNCTION: Hyperbolic cosine
 *   RETURN: Hyperbolic cosine
 *    PARAM: [IN] v - argument
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
double ch( const double v )
{
  return (exp(v) + exp(-v)) / 2.0;
} /* End of 'sh' function */

/***
 * FUNCTION: Calculate subtree value
 *    PARAM: [IN] tree - pointer to subtree root
 *    PARAM: [IN] val  - value
 *    THROW: Exception if an error occurred
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
double Equation::Calculate( const Vertex *tree, const double val ) const
{
  /* Determine vertex type */
  switch(tree->type)
  {
    /* Just number */
  case Equation::Number:
    return tree->val;

    /* Just constant */
  case Equation::Constant:
    return tree->val;

    /* Variable */
  case Equation::Variable:
    return val;

    /* Some parameter */
  case Equation::Parameter:
    if (tree->isSet)
      return tree->val;
    else
      throw Exception("Parameter <" + tree->param + "> is not set");
    break;

    /* Some function */
  case Equation::Function:
    {
      /* What is the function */
      switch (tree->func)
      {
      case ElementaryFunction::Exp:
        return exp(Calculate(tree->right, val));
      case ElementaryFunction::Log:
        return log(Calculate(tree->right, val));
      case ElementaryFunction::Sin:
        return sin(Calculate(tree->right, val));
      case ElementaryFunction::Cos:
        return cos(Calculate(tree->right, val));
      case ElementaryFunction::Tg:
        return tan(Calculate(tree->right, val));
      case ElementaryFunction::Ctg:
        return 1.0 / tan(Calculate(tree->right, val));
      case ElementaryFunction::Sh:
        return sh(Calculate(tree->right, val));
      case ElementaryFunction::Ch:
        return ch(Calculate(tree->right, val));
      } /* End of function switch */
    } /* Function case */
    break;

    /* Some operator */
  case Equation::BinaryOperator:
    {
      /* What is the operator */
      switch (tree->oper)
      {
      case Equation::Plus:
        return Calculate(tree->left, val) + Calculate(tree->right, val);
      case Equation::Minus:
        return Calculate(tree->left, val) - Calculate(tree->right, val);
      case Equation::Muliply:
        return Calculate(tree->left, val) * Calculate(tree->right, val);
      case Equation::Divide:
        return Calculate(tree->left, val) / Calculate(tree->right, val);
      case Equation::Power:
        return pow(Calculate(tree->left, val), Calculate(tree->right, val));
      } /* End of operator switch */
    } /* Operator case */
    break;
  } /* End of switch */

  /* That's it */
  return 0.0;
} /* End of 'Equation::Calculate' method */

/***
 * FUNCTION: Get function value by argument
 *   RETURN: Function value when x = val
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
double Equation::operator()( const double val ) const
{
  /* Tree is empty */
  if (!root)
    return 0.0;

  /* Calculate */
  return Calculate(root, val);
} /* End of 'Equation::operator() method */

/***
 * FUNCTION: Set's parameter's value by it's name
 *   RETURN: New equation with parameters
 *    PARAM: [IN] val - variable's value
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
Equation Equation::GetEquation( const double val ) const
{
  Equation copy = Equation(*this);
  copy.SetVariable(val);

  /* Simplify equation */
  copy.Simplify();

  /* That's it */
  return copy;
} /* End of 'Equation::GetEquation' method */
