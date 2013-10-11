/*           FILE: operators.cpp
 *           DATE: 18 Sep 2010 ã.
 *         AUTHOR: Eliseev Dmitry
 *        PROJECT: mathkernel
 *    LAST UPDATE: Updated on 18.09.2010
 *           NOTE: Operators of equation class implementation
 *
 * CONTACT PERSON: Eliseev Dmitry
 */

/* System modules including */
#include <sstream>

/* Engine modules including */

/* Project modules including */
#include "equation.h"

/***
 * Definitions and constants
 ***/

/***
 * Functions definition
 ***/

/***
 * FUNCTION: Make a copy of equation
 *    PARAM: [IN] equation - another equation
 *    THROW: Exception if an error occurred
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
Equation Equation::operator=( const Equation &equation )
{
  Release();

  /* Reset pointers */
  root   = NULL;
  source = NULL;

  /* Making copy */
  Copy(equation);
  return *this;
} /* End of 'Equation::operator=' method */

/***
 * FUNCTION: Make a sum of equations
 *    PARAM: [IN] equation - another equation
 *    THROW: Exception if an error occurred
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
Equation Equation::operator+( const Equation &equation )
{
  Equation temp("");

  /* One of elements is empty */
  if (!this->source)
    return Equation(equation);
  if (!equation.source)
    return Equation(*this);

  /* Making new common vertex */
  temp.root = new Vertex();
  temp.root->type   = BinaryOperator;
  temp.root->oper   = Plus;
  temp.root->weight = 1;
  temp.root->left  = CopyTree(this->root, temp.root);
  temp.root->right = CopyTree(equation.root, temp.root);

  /* Updating weight */
  UpdateWeight(temp.root->left, 1);
  UpdateWeight(temp.root->right, 1);

  /* Copying string representation */
  stringstream tempStream;
  tempStream << this->source << "+" << equation.source;
  string tempString;
  tempStream >> tempString;

  temp.source = new char[tempString.length() + 1];
  memset(temp.source, 0, tempString.length() + 1);
  memcpy(temp.source, tempString.c_str(), tempString.length());

  /* That's it */
  return temp;
} /* End of 'Equation::operator+' method */

/***
 * FUNCTION: Make a difference of equations
 *    PARAM: [IN] equation - another equation
 *    THROW: Exception if an error occurred
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
Equation Equation::operator-( const Equation &equation )
{
  Equation temp("");

  /* One of elements is empty */
  if (!this->source)
    return Equation("0") - equation;
  if (!equation.source)
    return Equation(*this);

  /* Making new common vertex */
  temp.root = new Vertex();
  temp.root->type   = BinaryOperator;
  temp.root->oper   = Minus;
  temp.root->weight = 1;
  temp.root->left  = CopyTree(this->root, temp.root);
  temp.root->right = CopyTree(equation.root, temp.root);

  /* Updating weight */
  UpdateWeight(temp.root->left, 1);
  UpdateWeight(temp.root->right, 1);

  /* Copying string representation */
  stringstream tempStream;
  tempStream << this->source << "-" << equation.source;
  string tempString;
  tempStream >> tempString;

  temp.source = new char[tempString.length() + 1];
  memset(temp.source, 0, tempString.length() + 1);
  memcpy(temp.source, tempString.c_str(), tempString.length());

  /* That's it */
  return temp;
} /* End of 'Equation::operator-' method */

/***
 * FUNCTION: Make a multiplication of equations
 *    PARAM: [IN] equation - another equation
 *    THROW: Exception if an error occurred
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
Equation Equation::operator*( const Equation &equation )
{
  Equation temp("");

  /* One of elements is empty */
  if (!(this->source&&equation.source))
    return Equation("0");

  /* Making new common vertex */
  temp.root = new Vertex();
  temp.root->type   = BinaryOperator;
  temp.root->oper   = Muliply;
  temp.root->weight = 1;
  temp.root->left  = CopyTree(this->root, temp.root);
  temp.root->right = CopyTree(equation.root, temp.root);

  /* Updating weight */
  UpdateWeight(temp.root->left, 1);
  UpdateWeight(temp.root->right, 1);

  temp.source = new char[strlen(this->source) + strlen(equation.source) + 6];
  memset(temp.source, 0, strlen(this->source) + strlen(equation.source) + 6);

  /* Copying string representation */
  stringstream tempStream;
  tempStream << "(" << this->source << ")*(" << equation.source << ")";
  string tempString;
  tempStream >> tempString;

  temp.source = new char[tempString.length() + 1];
  memset(temp.source, 0, tempString.length() + 1);
  memcpy(temp.source, tempString.c_str(), tempString.length());

  /* That's it */
  return temp;
} /* End of 'Equation::operator*' method */

/***
 * FUNCTION: Make a relation of equations
 *    PARAM: [IN] equation - another equation
 *    THROW: Exception if an error occurred
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
Equation Equation::operator/( const Equation &equation )
{
  Equation temp("");

  /* One of elements is empty */
  if (!this->source)
    return Equation("0");
  if (!equation.source)
    throw Exception("Division on zero");

  /* Making new common vertex */
  temp.root = new Vertex();
  temp.root->type   = BinaryOperator;
  temp.root->oper   = Divide;
  temp.root->weight = 1;
  temp.root->left  = CopyTree(this->root, temp.root);
  temp.root->right = CopyTree(equation.root, temp.root);

  /* Updating weight */
  UpdateWeight(temp.root->left, 1);
  UpdateWeight(temp.root->right, 1);

  temp.source = new char[strlen(this->source) + strlen(equation.source) + 6];
  memset(temp.source, 0, strlen(this->source) + strlen(equation.source) + 6);

  /* Copying string representation */
  stringstream tempStream;
  tempStream << "(" << this->source << ")/(" << equation.source << ")";
  string tempString;
  tempStream >> tempString;

  temp.source = new char[tempString.length() + 1];
  memset(temp.source, 0, tempString.length() + 1);
  memcpy(temp.source, tempString.c_str(), tempString.length());

  /* That's it */
  return temp;
} /* End of 'Equation::operator/' method */

/***
 * FUNCTION: Add equation
 *    PARAM: [IN] equation - another equation
 *    THROW: Exception if an error occurred
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
Equation Equation::operator+=( const Equation &equation )
{
  Equation copy = *this;
  copy = copy + equation;

  /* Making a copy */
  *this = copy;  
  return *this;
} /* End of '' method */

/***
 * FUNCTION: Difference with equation
 *    PARAM: [IN] equation - another equation
 *    THROW: Exception if an error occurred
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
Equation Equation::operator-=( const Equation &equation )
{
  Equation copy = *this;
  copy = copy - equation;

  /* Making a copy */
  *this = copy;  
  return *this;
} /* End of '' method */

/***
 * FUNCTION: Multiply on equation
 *    PARAM: [IN] equation - another equation
 *    THROW: Exception if an error occurred
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
Equation Equation::operator*=( const Equation &equation )
{
  Equation copy = *this;
  copy = copy * equation;

  /* Making a copy */
  *this = copy;  
  return *this;
} /* End of '' method */

/***
 * FUNCTION: Divide on equation
 *    PARAM: [IN] equation - another equation
 *    THROW: Exception if an error occurred
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
Equation Equation::operator/=( const Equation &equation )
{
  Equation copy = *this;
  copy = copy / equation;

  /* Making a copy */
  *this = copy;  
  return *this;
} /* End of '' method */