/*           FILE: equation.cpp
 *           DATE: 18 Sep 2010 ã.
 *         AUTHOR: EliseevDmitry
 *        PROJECT: mathkernel
 *    LAST UPDATE: Updated on 18.09.2010
 *           NOTE: Equation class implementation 
 *
 * CONTACT PERSON: Eliseev Dmitry
 */

/* System modules including */
#include <sstream>
#include <stack>

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
 * FUNCTION: Converts double to string
 *   RETURN: String representation of value
 *    PARAM: [IN] v - value to convert
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
string DoubleToString( const double &v )
{
  string sVal;
  stringstream ss;
  
  ss << v; 
  ss >> sVal;

  return sVal;
} /* End of 'DoubleToString' function */

/***
 * FUNCTION: Class default constructor
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
Equation::Vertex::Vertex( void )
{
  /* Reset pointers */
  parent = NULL;
  left   = NULL;
  right  = NULL;

  /* Default flags values */
  isSet        = false;
  isCalculable = false;

  /* Set default enum items */
  func = Equation::FunctionUnset;
  oper = Equation::OperatorUnset;
  type = Equation::TypeUnset;

  /* Reset values */
  val = 0.0;
  weight = 0;
  this->isSet = false;
} /* End of 'Equation::Vertex::Vertex' function */

/***
 * FUNCTION: Class constructor
 *    PARAM: [IN] equation - string with equation
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
Equation::Equation( const string &equation )
{
  source = NULL;
  root   = NULL;
  
  /* Build tree by string */
  try
  {
    ParseEquation(equation);
  }
  catch (Exception e)
  {
    Release();
    throw Exception(e);  	
  }  
} /* End of 'Equation::Equation' method */

/***
 * FUNCTION: Class constructor
 *    PARAM: [IN] number - just a number
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
Equation::Equation( const double number )
{
  source = NULL;
  root   = NULL;

  /* Transforming double to a string */
  string equation;
  stringstream ss;
  ss << number;
  ss >> equation;

  /* Build tree by string */
  try
  {
    ParseEquation(equation);
  }
  catch (Exception e)
  {
    Release();
    throw Exception(e);  	
  }  
} /* End of 'Equation::Equation' method */

/***
 * FUNCTION: Class copy constructor
 *    PARAM: [IN] equation - another equation
 *    THROW: Exception if an error occurred
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
Equation::Equation( const Equation &equation )
{
  /* Reset pointers */
  root = NULL;
  source = NULL;

  /* Making copy */
  Copy(equation);
} /* End of 'Equation::Equation' method */

/***
 * FUNCTION: Class destructor
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
Equation::~Equation( void )
{
  Release();
} /* End of 'Equation::~Equation' method */

/***
 * FUNCTION: Set's parameter's value by it's name
 *    PARAM: [IN] parameter - parameter's name
 *    PARAM: [IN] val       - parameter's value
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
void Equation::SetParameter( const string &parameter, const double val )
{
  /* There is no tree */
  if (!root)
    return;

  stack<Vertex*> verticesStack;
  verticesStack.push(root);

  /* Walking tree */
  while (!verticesStack.empty())
  {
    Vertex *cur = verticesStack.top();
    verticesStack.pop();

    /* Add children to stack */
    switch(cur->type)
    {
    case Equation::UnaryOperator:
    case Equation::Function:
      verticesStack.push(cur->right);
      break;
    case Equation::BinaryOperator:
      verticesStack.push(cur->left);
      verticesStack.push(cur->right);
      break; 
    case Equation::Parameter:
      if (cur->param == parameter)
      {
        cur->isSet = true;
        cur->val = val;
      }
      break;
    } /* End of switch */
  } /* End of while */
} /* End of 'Equation::SetParameter' method */

/***
 * FUNCTION: Set's variable's value
 *    PARAM: [IN] val - variable's value
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
void Equation::SetVariable( const double val )
{
  /* There is no tree */
  if (!root)
    return;

  stack<Vertex*> verticesStack;
  verticesStack.push(root);

  /* Walking tree */
  while (!verticesStack.empty())
  {
    Vertex *cur = verticesStack.top();
    verticesStack.pop();

    /* Add children to stack */
    switch(cur->type)
    {
    case Equation::UnaryOperator:
    case Equation::Function:
      verticesStack.push(cur->right);
      break;
    case Equation::BinaryOperator:
      verticesStack.push(cur->left);
      verticesStack.push(cur->right);
      break; 
    case Equation::Variable:
      cur->type = Number;
      cur->val  = val;
      break;
    } /* End of switch */
  } /* End of while */
} /* End of 'Equation::SetVariable' method */

/***
 * FUNCTION: Remove subtree
 *    PARAM: [IN] tree - pointer to subtree root
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
void Equation::RemoveSubtree( Vertex *tree )
{
  /* There is no tree */
  if (!tree)
    return;

  stack<Vertex*> verticesStack;
  verticesStack.push(tree);

  /* Walking tree */
  while (!verticesStack.empty())
  {
    Vertex *cur = verticesStack.top();
    verticesStack.pop();

    /* Wrong pointer */
    if (!cur)
      continue;

    /* Add children to stack */
    switch(cur->type)
    {
    case Equation::UnaryOperator:
    case Equation::Function:
      verticesStack.push(cur->right);
      break;
    case Equation::BinaryOperator:
      verticesStack.push(cur->left);
      verticesStack.push(cur->right);
      break; 
    } /* End of switch */

    /* Self removing */
    delete cur;
  } /* End of while */
  tree = NULL;
} /* End of 'Equation::RemoveSubtree' method */

/***
 * FUNCTION: Remove built tree
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
void Equation::RemoveTree( void )
{
  RemoveSubtree(root);
  root = NULL;
} /* End of 'Equation::RemoveTree' method */

/***
 * FUNCTION: Prints to console built tree
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
void Equation::PrintTree( void )
{
  PrintSubTree(root);
} /* End of 'Equation::PrintTree' method */

/***
 * FUNCTION: Release memory
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
void Equation::Release( void )
{
  /* Remove built tree */
  RemoveTree();

  /* Remove source equation */
  if (source)
    delete[] source;

  /* Reset pointers */
  source = NULL;
  root   = NULL;
} /* End of 'Equation::Release' method */

/***
 * FUNCTION: Get original equation string representation
 *   RETURN: Original equation string representation
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
const char* Equation::GetExpression( void ) const
{
  return source;
} /* End of 'Equation::GetExpression' method */

/***
 * FUNCTION: Make a copy of equation
 *    PARAM: [IN] equation - another equation
 *    THROW: Exception if an error occurred
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
void Equation::Copy( const Equation &equation )
{
  /* Empty equation */
  if (!equation.source)
    return;

  /* Copying original equation */
  source = new char[strlen(equation.source) + 1];
  memset(source, 0, strlen(equation.source) + 1);
  memcpy(source, equation.source, strlen(equation.source));

  /* Copying built tree */
  root = CopyTree(equation.root);
} /* End of 'Equation::Copy' method */

/***
 * FUNCTION: Make a copy of another tree
 *   RETURN: Tree copy
 *    PARAM: [IN] root   - pointer to source tree root
 *    PARAM: [IN] parent - pointer to parent node
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
Equation::Vertex* Equation::CopyTree( const Vertex *treeRoot, Vertex *parent )
{
  /* There is no tree */
  if (!treeRoot)
    return NULL;

  /* New node creation */
  Vertex *newNode = new Vertex();
  *newNode = *treeRoot;

  /* Changing parent to correct */
  newNode->parent = parent;

  /* Copying subtrees */
  newNode->left  = CopyTree(treeRoot->left, newNode);
  newNode->right = CopyTree(treeRoot->right, newNode);

  /* That's it */
  return newNode;
} /* End of 'Equation::CopyTree' method */

/***
 * FUNCTION: Saves equation to external file
 *    PARAM: [IN] filename - file to save
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
void Equation::SaveToFile( const string &filename ) const
{
  /* Making string representation */
  string strPresentation = BuildString();

  /* Output to file */
  FILE *f = fopen(filename.c_str(), "wt");
  fputs(strPresentation.c_str(), f);
  fclose(f); 
} /* End of 'Equation::SaveToFile' method */

/***
 * FUNCTION: Get string representation of equation
 *   RETURN: String representation of equation
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
string Equation::ToString( void ) const
{
  return BuildString();
} /* End of 'Equation::ToString' method */

/***
* FUNCTION: Loads equation from external file
*    PARAM: [IN] filename - file to load
*      SEE: write me
*   AUTHOR: Eliseev Dmitry
***/
void Equation::LoadFromFile( const string &filename )
{
  Release();

  /* Opening file */
  FILE *f = fopen(filename.c_str(), "rt");
  if (!f)
    throw Exception("File not found");

  /* Reading data */
  fseek(f, 0, SEEK_END);
  unsigned long fileSize = ftell(f);

  if (fileSize == 0)
  {
    fclose(f);
    throw Exception("File is empty");
  }

  char *tempData = new char[fileSize + 1];
  memset(tempData, 0, fileSize + 1);
  fseek(f, 0, SEEK_SET);
  fgets(tempData, fileSize + 1, f);
  fclose(f);

  /* New equation creation */
  try
  {
    Equation newEquation(tempData);
    *this = newEquation;
  }
  catch (Exception e)
  {
    /* Release memory */
    delete[] tempData;

    throw e;
  }
  
  /* Release memory */
  delete[] tempData;
} /* End of 'Equation::LoadFromFile' method */

/***
 * FUNCTION: Build string representation by equation
 *   RETURN: Equation's string representation
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
string Equation::BuildString( void ) const
{
  return BuildSubstring(root);  
} /* End of 'Equation::BuildString' method */

/***
 * FUNCTION: Build string representation by equation of subtree
 *   RETURN: Equation's subtree string representation
 *    PARAM: [IN] tree - pointer to subtree root
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
string Equation::BuildSubstring( const Vertex *tree ) const
{
  if (!tree)
    return string("");

  /* What is the vertex? */
  switch(tree->type)
  {
    /* Nothing to simplify */
  case Number:  
  case Constant:
    return DoubleToString(tree->val);

    /* Parameter was set */
  case Parameter:
    if (tree->isSet)
      return DoubleToString(tree->val);
    else
      return tree->param;

    /* Function */
  case Function:
    return GetFunctionName(tree->func) + string("(") + BuildSubstring(tree->right) + string(")");

    /* Variable */
  case Variable:
    return string("x");

    /* Binary operator */
  case BinaryOperator:
    return string("(") + BuildSubstring(tree->left) + string(") ") + GetOperatorSymbol(tree->oper) +
           string(" (") + BuildSubstring(tree->right) + string(")");
  } 

  /* End of building string */
  return string("");
} /* End of 'Equation::BuildSubstring' method */