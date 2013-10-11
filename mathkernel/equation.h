#ifndef __EQUATION_H__634204131734375000
#define __EQUATION_H__634204131734375000

/*           FILE: equation.h
 *           DATE: 18 Sep 2010 ã.
 *         AUTHOR: Eliseev Dmitry
 *        PROJECT: mathkernel
 *    LAST UPDATE: Updated on 18.09.2010
 *           NOTE: Equation class definition
 *
 * CONTACT PERSON: Eliseev Dmitry
 */

/* System modules including */
#include <string>
#include <map>

/* Engine modules including */

/* Project modules including */
#include "exception.h"
#include "constants.h"

/***
 * Definitions and constants
 ***/

/* Sharing standard namespace */
using namespace std;

/* Classes definition */
class DllExport Equation
{
  /*** Definitions ***/

  /* Vertex type enum */
  enum VertexType { TypeUnset, Number, UnaryOperator, BinaryOperator, Function, Parameter, Variable, Constant };

  /* Elementary functions enum */
  enum ElementaryFunction { FunctionUnset, Exp, Log, Sin, Cos, Tg, Ctg, Sh, Ch };

  /* Operators */
  enum Operator { OperatorUnset, Plus, Minus, Muliply, Divide, Power };

  /* Place to add new vertex */
  enum VertexPlace { Here, Left, Right };

  /* Vertex class */
  struct Vertex
  {
    /* Data */
    VertexType type;         /* Type of current vertex */
    Operator oper;           /* If vertex is operator, here is operator's type */
    ElementaryFunction func; /* If vertex is function, here is function's type */
    double val;              /* If vertex is number, here is number's value */
    string param;            /* If vertex is parameter, here is parameter's name */

    bool isSet;              /* If vertex parameter already set */
    bool isCalculable;       /* Calculable flag */

    unsigned int weight;     /* Current node weight (priority) */

    /* Pointers */
    Vertex *parent;          /* Pointer to parent vertex */
    Vertex *left;            /* Left operand */
    Vertex *right;           /* Right operand */

    /***
     * FUNCTION: Class default constructor
     *      SEE: write me
     *   AUTHOR: Eliseev Dmitry
     ***/
    Vertex( void );
  }; /* End of 'Vertex' class */

  /*** Members ***/

  /* Equation tree */
  Vertex *root;

  /* Source equation */
  char *source;

  /***
   * FUNCTION: Parse string representation of equation and build equation tree
   *    PARAM: [IN] equation - string with equation
   *    THROW: Exception if an error occurred
   *      SEE: write me
   *   AUTHOR: Eliseev Dmitry
   ***/
  void ParseEquation( const string &equation );

  /***
   * FUNCTION: Determine operator's type by it char representation
   *   RETURN: Operator's type
   *    PARAM: [IN] symbol - operator's char representation
   *    THROW: Exception if an error occurred
   *      SEE: write me
   *   AUTHOR: Eliseev Dmitry
   ***/
  Operator GetOperatorType( const char symbol ) const;

  /***
   * FUNCTION: Determine operator's symbol by type
   *   RETURN: Operator's symbol
   *    PARAM: [IN] oper - operator's type
   *      SEE: write me
   *   AUTHOR: Eliseev Dmitry
   ***/
  const char GetOperatorSymbol( const Operator oper ) const;

  /***
   * FUNCTION: Determine function's type by it char representation
   *   RETURN: Function's type
   *    PARAM: [IN] symbol - function's char representation
   *    THROW: Exception if an error occurred
   *      SEE: write me
   *   AUTHOR: Eliseev Dmitry
   ***/
  ElementaryFunction GetFunctionType( const string &f ) const;

  /***
   * FUNCTION: Get function name by it's type
   *   RETURN: Function name
   *    PARAM: [IN] func - function type
   *      SEE: write me
   *   AUTHOR: Eliseev Dmitry
   ***/
  string GetFunctionName( const ElementaryFunction func ) const;

  /***
   * FUNCTION: Determine constant value by it's string representation
   *   RETURN: Constant value
   *    PARAM: [IN] c - constant string representation
   *      SEE: write me
   *   AUTHOR: Eliseev Dmitry
   ***/
  double GetConstantValue( const string &c ) const;

  /***
   * FUNCTION: Links two vertices's
   *    PARAM: [IN] children - pointer to child vertex
   *    PARAM: [IN] parent   - pointer to parent
   *    PARAM: [IN] place    - place to add
   *      SEE: write me
   *   AUTHOR: Eliseev Dmitry
   ***/
  void VertexLink( Vertex *children, Vertex *parent, const VertexPlace place );

  /***
   * FUNCTION: Links two vertices's
   *    PARAM: [IN] parent   - pointer to parent vertex
   *    PARAM: [IN] oldChild - pointer to old vertex
   *    PARAM: [IN] newChild - pointer to new vertex
   *      SEE: write me
   *   AUTHOR: Eliseev Dmitry
   ***/
  void VertexChange( Vertex *parent, Vertex *oldChild, Vertex *newChild );

  /***
   * FUNCTION: Find place to add new vertex by operator's weight
   *   RETURN: Pointer to vertex in tree to replace it with operator
   *    PARAM: [IN] current - pointer to current vertex
   *    PARAM: [IN] weight  - operator weight
   *      SEE: write me
   *   AUTHOR: Eliseev Dmitry
   ***/
  Vertex *VertexPlaceFind( Vertex *current, const unsigned int weight ) const;
 
  /***
   * FUNCTION: Remove built tree
   *      SEE: write me
   *   AUTHOR: Eliseev Dmitry
   ***/
  void RemoveTree( void );

  /***
   * FUNCTION: Remove subtree
   *    PARAM: [IN] tree - pointer to subtree root
   *      SEE: write me
   *   AUTHOR: Eliseev Dmitry
   ***/
  void RemoveSubtree( Vertex *tree );

  /***
   * FUNCTION: Make a copy of another tree
   *   RETURN: Tree copy
   *    PARAM: [IN] root - pointer to source tree root
   *    PARAM: [IN] parent - pointer to parent node
   *      SEE: write me
   *   AUTHOR: Eliseev Dmitry
   ***/
  Vertex* CopyTree( const Vertex *treeRoot, Vertex *parent = NULL );

  /***
   * FUNCTION: Release memory
   *      SEE: write me
   *   AUTHOR: Eliseev Dmitry
   ***/
  void Release( void );

  /***
   * FUNCTION: Update subtree and set new priority
   *   RETURN: Pointer to subtree root
   *    PARAM: [IN] current - pointer to subtree root
   *    PARAM: [IN] weight  - operator weight
   *      SEE: write me
   *   AUTHOR: Eliseev Dmitry
   ***/
  void UpdateWeight( Vertex *current, const unsigned int weight );

  /***
   * FUNCTION: Prints to console built subtree
   *    PARAM: [IN] current    - pointer to subtree root
   *    PARAM: [IN] currentTab - current tabulation
   *      SEE: write me
   *   AUTHOR: Eliseev Dmitry
   ***/
  void PrintSubTree( const Vertex *current, const unsigned int currentTab = 0 );

  /***
   * FUNCTION: Calculate subtree value
   *    PARAM: [IN] tree - pointer to subtree root
   *    PARAM: [IN] val  - value
   *    THROW: Exception if an error occurred
   *      SEE: write me
   *   AUTHOR: Eliseev Dmitry
   ***/
  double Calculate( const Vertex *tree, const double val ) const;

  /***
   * FUNCTION: Moving to parent from current vertex
   *   RETURN: Pointer to tree's root
   *    PARAM: [IN] current - pointer to current vertex
   *      SEE: write me
   *   AUTHOR: Eliseev Dmitry
   ***/
  Vertex* GetParent( Vertex *current ) const;

  /***
   * FUNCTION: Make a copy of equation
   *    PARAM: [IN] equation - another equation
   *    THROW: Exception if an error occurred
   *      SEE: write me
   *   AUTHOR: Eliseev Dmitry
   ***/
  void Copy( const Equation &equation );

  /***
   * FUNCTION: Set's variable's value
   *    PARAM: [IN] val - variable's value
   *      SEE: write me
   *   AUTHOR: Eliseev Dmitry
   ***/
  void SetVariable( const double val );

  /***
   * FUNCTION: Simplify subtree
   *    PARAM: [IN] tree - pointer to subtree root
   *      SEE: write me
   *   AUTHOR: Eliseev Dmitry
   ***/
  void SimplifySubtree( Vertex *tree );

  /***
   * FUNCTION: Build string representation by equation of subtree
   *   RETURN: Equation's subtree string representation
   *    PARAM: [IN] tree - pointer to subtree root
   *      SEE: write me
   *   AUTHOR: Eliseev Dmitry
   ***/
  string BuildSubstring( const Vertex *tree ) const;

  /***
   * FUNCTION: Build string representation by equation
   *   RETURN: Equation's string representation
   *      SEE: write me
   *   AUTHOR: Eliseev Dmitry
   ***/
  string BuildString( void ) const;

  /* Public members */
public:
  /***
   * FUNCTION: Class constructor
   *    PARAM: [IN] equation - string with equation
   *    THROW: Exception if an error occurred
   *      SEE: write me
   *   AUTHOR: Eliseev Dmitry
   ***/
  Equation( const string &equation );

  /***
   * FUNCTION: Class constructor
   *    PARAM: [IN] number - just a number
   *      SEE: write me
   *   AUTHOR: Eliseev Dmitry
   ***/
  Equation( const double number );

  /***
   * FUNCTION: Class copy constructor
   *    PARAM: [IN] equation - another equation
   *    THROW: Exception if an error occurred
   *      SEE: write me
   *   AUTHOR: Eliseev Dmitry
   ***/
  Equation( const Equation &equation );

  /***
   * FUNCTION: Class destructor
   *      SEE: write me
   *   AUTHOR: Eliseev Dmitry
   ***/
  ~Equation( void );

  /***
   * FUNCTION: Saves equation to external file
   *    PARAM: [IN] filename - file to save
   *      SEE: write me
   *   AUTHOR: Eliseev Dmitry
   ***/
  void SaveToFile( const string &filename ) const;

  /***
   * FUNCTION: Loads equation from external file
   *    PARAM: [IN] filename - file to load
   *      SEE: write me
   *   AUTHOR: Eliseev Dmitry
   ***/
  void LoadFromFile( const string &filename );

  /***
   * FUNCTION: Set's parameter's value by it's name
   *    PARAM: [IN] parameter - parameter's name
   *    PARAM: [IN] val       - parameter's value
   *      SEE: write me
   *   AUTHOR: Eliseev Dmitry
   ***/
  void SetParameter( const string &parameter, const double val );

  /***
   * FUNCTION: Get copy of equation with already set variable
   *   RETURN: New equation with parameters
   *    PARAM: [IN] val - variable's value
   *      SEE: write me
   *   AUTHOR: Eliseev Dmitry
   ***/
  Equation GetEquation( const double val ) const;

  /***
   * FUNCTION: Get function value by argument
   *   RETURN: Function value when x = val
   *    THROW: Exception if error occurred
   *      SEE: write me
   *   AUTHOR: Eliseev Dmitry
   ***/
  double operator()( const double val ) const;

  /***
   * FUNCTION: Prints to console built tree
   *      SEE: write me
   *   AUTHOR: Eliseev Dmitry
   ***/
  void PrintTree( void );

  /***
   * FUNCTION: Get original equation string representation
   *   RETURN: Original equation string representation
   *      SEE: write me
   *   AUTHOR: Eliseev Dmitry
   ***/
  const char* GetExpression( void ) const;

  /***
   * FUNCTION: Simplify equation's tree
   *      SEE: write me
   *   AUTHOR: Eliseev Dmitry
   ***/
  void Simplify( void );
  
  /***
   * FUNCTION: Get string representation of equation
   *   RETURN: String representation of equation
   *      SEE: write me
   *   AUTHOR: Eliseev Dmitry
   ***/
  string ToString( void ) const;

  /***
   * FUNCTION: Make a copy of equation
   *    PARAM: [IN] equation - another equation
   *    THROW: Exception if an error occurred
   *      SEE: write me
   *   AUTHOR: Eliseev Dmitry
   ***/
  Equation operator=( const Equation &equation );

  /***
   * FUNCTION: Make a sum of equations
   *    PARAM: [IN] equation - another equation
   *    THROW: Exception if an error occurred
   *      SEE: write me
   *   AUTHOR: Eliseev Dmitry
   ***/
  Equation operator+( const Equation &equation );

  /***
   * FUNCTION: Make a difference of equations
   *    PARAM: [IN] equation - another equation
   *    THROW: Exception if an error occurred
   *      SEE: write me
   *   AUTHOR: Eliseev Dmitry
   ***/
  Equation operator-( const Equation &equation );

  /***
   * FUNCTION: Make a multiplication of equations
   *    PARAM: [IN] equation - another equation
   *    THROW: Exception if an error occurred
   *      SEE: write me
   *   AUTHOR: Eliseev Dmitry
   ***/
  Equation operator*( const Equation &equation );

  /***
   * FUNCTION: Make a relation of equations
   *    PARAM: [IN] equation - another equation
   *    THROW: Exception if an error occurred
   *      SEE: write me
   *   AUTHOR: Eliseev Dmitry
   ***/
  Equation operator/( const Equation &equation );

  /***
   * FUNCTION: Add equation
   *    PARAM: [IN] equation - another equation
   *    THROW: Exception if an error occurred
   *      SEE: write me
   *   AUTHOR: Eliseev Dmitry
   ***/
  Equation operator+=( const Equation &equation );

  /***
   * FUNCTION: Difference with equation
   *    PARAM: [IN] equation - another equation
   *    THROW: Exception if an error occurred
   *      SEE: write me
   *   AUTHOR: Eliseev Dmitry
   ***/
  Equation operator-=( const Equation &equation );

  /***
   * FUNCTION: Multiply on equation
   *    PARAM: [IN] equation - another equation
   *    THROW: Exception if an error occurred
   *      SEE: write me
   *   AUTHOR: Eliseev Dmitry
   ***/
  Equation operator*=( const Equation &equation );

  /***
   * FUNCTION: Divide on equation
   *    PARAM: [IN] equation - another equation
   *    THROW: Exception if an error occurred
   *      SEE: write me
   *   AUTHOR: Eliseev Dmitry
   ***/
  Equation operator/=( const Equation &equation );
}; /* End of 'Equation' class */

#endif /* __EQUATION_H__634204131734375000 */
