/*           FILE: parser.cpp
 *           DATE: 18 Sep 2010 ã.
 *         AUTHOR: Eliseev Dmitry
 *        PROJECT: mathkernel
 *    LAST UPDATE: Updated on 18.09.2010
 *           NOTE: Equation class parsing methods implementation
 *
 * CONTACT PERSON: Eliseev Dmitry
 */

/* System modules including */
#include <algorithm>
#include <iostream>

/* Engine modules including */

/* Project modules including */
#include "equation.h"

/***
 * Definitions and constants
 ***/

/*** Operators definition ***/
const char c_OperatorPlus     = '+';
const char c_OperatorMinus    = '-';
const char c_OperatorMultiply = '*';
const char c_OperatorDivide   = '/';
const char c_OperatorPower    = '^';

/* Unset operator */
const char c_OperatorUnset    = '@';

/*** Brackets definition ***/
const char c_BracketRoundOpen  = '(';
const char c_BracketRoundClose = ')';
const char c_BracketRectOpen   = '[';
const char c_BracketRectClose  = ']';

/*** Operators weights ***/
const unsigned int c_WeightPlus    = 1;
const unsigned int c_WeightMult    = 2;
const unsigned int c_WeightPower   = 3;
const unsigned int c_WeightFunc    = 4;
const unsigned int c_WeightBracket = 5;

/*** Defined constants ***/
const string c_ConstantPI = "PI";
const string c_ConstantE  = "E";

/*** Variable ***/
const string c_Variable = "x";

/*** Elementary functions ***/
const string c_FunctionExp = "Exp";
const string c_FunctionLog = "Log";
const string c_FunctionSin = "Sin";
const string c_FunctionCos = "Cos";
const string c_FunctionTg  = "Tg";
const string c_FunctionCtg = "Ctg";
const string c_FunctionSh  = "Sh";
const string c_FunctionCh  = "Ch";

/*** Expectation ***/
const unsigned int c_ExpectAny      = 0; /* Everything is possible */
const unsigned int c_ExpectValue    = 1; /* Constant, variable, function, parameter or brackets */
const unsigned int c_ExpectOperator = 2; /* Any operator or brackets */

/*** Expectation strings ***/
const string c_ExpectAnyDescription      = "everything";
const string c_ExpectValueDescription    = "constant, value, variable, parameter, function";
const string c_ExpectOperatorDescription = "operator";

/***
 * Functions definition
 ***/

/***
 * FUNCTION: Converts string to lower register
 *   RETURN: Source string, converted to low register
 *    PARAM: [IN] s - string to convert
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
string ToLower( const string &s )
{
  string d(s);
  transform(d.begin (), d.end (), d.begin (), (int(*)(int))tolower);
  return d;
} /* End of 'ToLower' function */

/***
 * FUNCTION: Replace all occurrences of "what" string in "src" string with "with" string
 *    PARAM: [IN] src  - string-container
 *    PARAM: [IN] what - substring to replace
 *    PARAM: [IN] with - new string
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
void ReplaceAll( string &src, const string &what, const string &with )
{    
  if (what != with) 
  {
    string temp;
    string::size_type prev_pos = 0, pos = src.find(what, 0);

    while (string::npos != pos) 
    {
      temp += string(src.begin() + prev_pos, src.begin() + pos) + with;
      prev_pos = pos + what.size();
      pos = src.find(what, prev_pos);
    }

    if (!temp.empty()) 
    {
      src = temp + string(src.begin() + prev_pos, src.end());

      if (string::npos == with.find(what)) 
        ReplaceAll(src, what, with);
    }
  }
} /* End of 'ReplaceAll' function */

/***
 * FUNCTION: Check symbol
 *   RETURN: TRUE if symbol is alpha, FALSE otherwise
 *    PARAM: [IN] symbol - symbol to check
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
inline bool IsAlpha( const char symbol )
{
  return ((symbol >= 'a')&&(symbol <= 'z'))||((symbol >= 'A')&&(symbol <= 'Z'));
} /* End of 'IsAlpha' function */

/***
 * FUNCTION: Check symbol
 *   RETURN: TRUE if symbol is digit, FALSE otherwise
 *    PARAM: [IN] symbol - symbol to check
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
inline bool IsDigit( const char symbol )
{
  return (symbol >= '0')&&(symbol <= '9');
} /* End of 'IsDigit' function */

/***
 * FUNCTION: Check symbol
 *   RETURN: TRUE if symbol is one of round bracket, FALSE otherwise
 *    PARAM: [IN] symbol - symbol to check
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
inline bool IsBracketRound( const char symbol )
{
  return (symbol == c_BracketRoundOpen)||(symbol == c_BracketRoundClose);
} /* End of 'IsBracketRound' function */

/***
 * FUNCTION: Check symbol
 *   RETURN: TRUE if symbol is one of rectangle bracket, FALSE otherwise
 *    PARAM: [IN] symbol - symbol to check
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
inline bool IsBracketRect( const char symbol )
{
  return (symbol == c_BracketRectOpen)||(symbol == c_BracketRectClose);
} /* End of 'IsBracketRect' function */

/***
 * FUNCTION: Check symbol
 *   RETURN: TRUE if symbol is one of bracket, FALSE otherwise
 *    PARAM: [IN] symbol - symbol to check
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
inline bool IsBracket( const char symbol )
{
  return IsBracketRect(symbol) || IsBracketRound(symbol);
} /* End of 'IsBracket' function */

/***
 * FUNCTION: Check symbol
 *   RETURN: TRUE if symbol is one of operator, FALSE otherwise
 *    PARAM: [IN] symbol - symbol to check
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
inline bool IsOperator( const char symbol )
{
  return (symbol == c_OperatorMinus) || (symbol == c_OperatorPlus) || 
         (symbol == c_OperatorMultiply) || (symbol == c_OperatorDivide) ||
         (symbol == c_OperatorPower);
} /* End of 'IsOperator' function */

/***
 * FUNCTION: Check symbol
 *   RETURN: TRUE if symbol is special symbol (one of c_XXX constants), FALSE otherwise
 *    PARAM: [IN] symbol - symbol to check
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
inline bool IsSpecial( const char symbol )
{
  return IsBracket(symbol) || IsOperator(symbol);
} /* End of 'IsSpecial' function */

/***
 * FUNCTION: Check symbol
 *   RETURN: TRUE if symbol is a point symbol, FALSE otherwise
 *    PARAM: [IN] symbol - symbol to check
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
inline bool IsPoint( const char symbol )
{
  return symbol == '.';
} /* End of 'IsPoint' function */

/***
 * FUNCTION: Check symbol
 *   RETURN: TRUE if symbol is wrong, FALSE otherwise
 *    PARAM: [IN] symbol - symbol to check
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
inline bool IsWrongSymbol( const char symbol )
{
  return !(IsBracketRound(symbol) || IsOperator(symbol) || IsDigit(symbol) || IsAlpha(symbol) || IsPoint(symbol));
} /* End of 'IsWrongSymbol' function */

/***
 * FUNCTION: Case-insensitive string comparison
 *   RETURN: TRUE if strings are equal, FALSE otherwise
 *    PARAM: [IN] f - first string to compare
 *    PARAM: [IN] s - second string to compare
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
inline bool AreStringsEqual( const string &f, const string &s )
{
  return ToLower(f) == ToLower(s);
} /* End of 'AreStringsEqual' function */

/***
 * FUNCTION: Check string
 *   RETURN: TRUE if string is known constant, FALSE otherwise
 *    PARAM: [IN] s - string to check
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
inline bool IsConstant( const string &s )
{
  return AreStringsEqual(s, c_ConstantPI) || AreStringsEqual(s, c_ConstantE);
} /* End of 'IsConstant' function */

/***
 * FUNCTION: Check string
 *   RETURN: TRUE if string is variable, FALSE otherwise
 *    PARAM: [IN] s - string to check
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
inline bool IsVariable( const string &s )
{
  return AreStringsEqual(s, c_Variable);
} /* End of 'IsVariable' function */

/***
 * FUNCTION: Check string
 *   RETURN: TRUE if string is known elementary function, FALSE otherwise
 *    PARAM: [IN] s - string to check
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
inline bool IsFunction( const string &s )
{
  return AreStringsEqual(s, c_FunctionExp) || 
         AreStringsEqual(s, c_FunctionLog) || 
         AreStringsEqual(s, c_FunctionSin) ||
         AreStringsEqual(s, c_FunctionCos) ||
         AreStringsEqual(s, c_FunctionTg)  ||
         AreStringsEqual(s, c_FunctionCtg) ||
         AreStringsEqual(s, c_FunctionSh)  ||
         AreStringsEqual(s, c_FunctionCh);
} /* End of 'IsFunction' function */

/***
 * FUNCTION: Determine operator weight
 *   RETURN: Operator weight
 *    PARAM: [IN] symbol - operator char representation (+, -, *, /, ^)
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
inline unsigned int GetOperatorWeight( const char symbol )
{
  /* Determine weight */
  switch(symbol)
  {
  case c_OperatorPlus:
  case c_OperatorMinus:
    return c_WeightPlus;
  case c_OperatorMultiply:
  case c_OperatorDivide:
    return c_WeightMult;
  case c_OperatorPower:
    return c_WeightPower;
  }

  /* Unknown operator */
  throw Exception("Unknown operator");
} /* End of 'GetOperatorWeight' function */

/***
 * FUNCTION: Determine operator's type by it char representation
 *   RETURN: Operator's type
 *    PARAM: [IN] symbol - operator's char representation
 *    THROW: Exception if an error occurred
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
Equation::Operator Equation::GetOperatorType( const char symbol ) const
{
  /* Determine type */
  switch(symbol)
  {
  case c_OperatorPlus:
    return Equation::Plus;
  case c_OperatorMinus:
    return Equation::Minus;
  case c_OperatorMultiply:
    return Equation::Muliply;
  case c_OperatorDivide:
    return Equation::Divide;
  case c_OperatorPower:
    return Equation::Power;
  }

  /* Unknown operator */
  throw Exception("Unknown operator");
} /* End of 'Equation::GetOperatorType' method */

/***
 * FUNCTION: Determine operator's symbol by type
 *   RETURN: Operator's symbol
 *    PARAM: [IN] oper - operator's type
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
const char Equation::GetOperatorSymbol( const Operator oper ) const
{
  switch (oper)
  {
  case Equation::Plus:
    return c_OperatorPlus;
  case Equation::Minus:
    return c_OperatorMinus;
  case Equation::Muliply:
    return c_OperatorMultiply;
  case Equation::Divide:
    return c_OperatorDivide;
  case Equation::Power:
    return c_OperatorPower;
  }

  /* Unknown operator */
  return c_OperatorUnset;
} /* End of 'Equation::GetOperatorType' method */

/***
 * FUNCTION: Determine constant value by it's string representation
 *   RETURN: Constant value
 *    PARAM: [IN] c - constant string representation
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
double Equation::GetConstantValue( const string &c ) const
{
  if (AreStringsEqual(c, c_ConstantE))
    return ::Constants::E;
  if (AreStringsEqual(c, c_ConstantPI))
    return ::Constants::PI;
  
  /* Unknown constant */
  throw Exception("Unknown constant: " + c);
} /* End of 'Equation::GetConstantValue' method */

/***
 * FUNCTION: Determine function's type by it char representation
 *   RETURN: Function's type
 *    PARAM: [IN] symbol - function's char representation
 *    THROW: Exception if an error occurred
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
Equation::ElementaryFunction Equation::GetFunctionType( const string &f ) const
{
  if (AreStringsEqual(f, c_FunctionExp))
    return Equation::Exp;
  if (AreStringsEqual(f, c_FunctionLog))
    return Equation::Log;
  if (AreStringsEqual(f, c_FunctionSin))
    return Equation::Sin;
  if (AreStringsEqual(f, c_FunctionCos))
    return Equation::Cos;
  if (AreStringsEqual(f, c_FunctionTg))
    return Equation::Tg;
  if (AreStringsEqual(f, c_FunctionCtg))
    return Equation::Ctg;
  if (AreStringsEqual(f, c_FunctionSh))
    return Equation::Sh;
  if (AreStringsEqual(f, c_FunctionCh))
    return Equation::Ch;

  /* Unknown function */
  throw Exception("Unknown function: " + f);
} /* End of 'Equation::GetFunctionType' method */

/***
 * FUNCTION: Get function name by it's type
 *   RETURN: Function name
 *    PARAM: [IN] func - function type
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
string Equation::GetFunctionName( const ElementaryFunction func ) const
{
  /* Determine function */
  switch (func)
  {
  case Equation::Exp:
    return string(c_FunctionExp);
  case Equation::Log:
    return string(c_FunctionLog);
  case Equation::Sin:
    return string(c_FunctionSin);
  case Equation::Cos:
    return string(c_FunctionCos);
  case Equation::Tg:
    return string(c_FunctionTg);
  case Equation::Ctg:
    return string(c_FunctionCtg);
  case Equation::Sh:
    return string(c_FunctionSh);
  case Equation::Ch:
    return string(c_FunctionCh);
  }

  /* Function is unknown */
  return "UnknownFunction";
} /* End of 'Equation::GetFunctionName' method */

/***
 * FUNCTION: Determine description by term
 *   RETURN: Term description
 *    PARAM: [IN] term - one of c_ExpectXXX consts
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
string GetTerm( const unsigned int term )
{
  switch (term)
  {
  case c_ExpectAny:
    return c_ExpectAnyDescription;
  case c_ExpectValue:
    return c_ExpectValueDescription;
  case c_ExpectOperator:
    return c_ExpectOperatorDescription;
  } /* End of switch */

  /* Everything is possible */
  return c_ExpectAnyDescription;
} /* End of 'GetTerm function ' */

/***
 * FUNCTION: Validate equation
 *    PARAM: [IN] equation - equation to validate
 *    THROW: Exception if equation is wrong
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
void ValidateEquation( const string &equation )
{
  unsigned int pos = 0;
  int numBrackets = 0;
  char prevSymbol = 0;

  /* First character is operator */
  if (IsOperator(equation.c_str()[0]))
    throw Exception("Equation can't starts with operator");

  /* Determine number of brackets */
  for (pos = 0; pos < equation.length(); pos++)
  {    
    const char curChar = equation.c_str()[pos];

    /* Wrong symbol */
    if (IsWrongSymbol(curChar))
      throw Exception("Equation contain wrong character");

    /* Number of brackets */
    if (curChar == c_BracketRoundOpen)
      numBrackets++;
    if (curChar == c_BracketRoundClose)
      numBrackets--;

    /* Two operators */
    if (IsOperator(curChar)&&IsOperator(prevSymbol))
      throw Exception("Equation contain two operators near");

    /* Storing previous symbol */
    prevSymbol = equation.c_str()[pos];
  } /* Processing string */

  if (numBrackets != 0)
    throw Exception("Incorrect number of brackets");
} /* End of 'ValidateEquation' function */

/***
 * FUNCTION: Parse string representation of equation and build equation tree
 *    PARAM: [IN] equation - string with equation
 *    THROW: Exception if an error occurred
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
void Equation::ParseEquation( const string &equation )
{
  /* Remove spaces from equation */
  string expression = equation;
  ReplaceAll(expression, " ", "");

  /* Expression is empty */
  if (expression.empty())
    return;

  /* Trying to validate equation */
  ValidateEquation(expression);

  /* Storing original equation */
  source = new char[expression.length() + 1];
  memset(source, 0, expression.length() + 1);
  memcpy(source, expression.c_str(), expression.length());

  /* Creation of tree */
  VertexPlace place = Equation::Here;
  Vertex *current = NULL;
  
  /* Conversation to c-style string (chars array) */
  const char *pEquation = expression.c_str();

  /* Additional brackets weight */
  unsigned int bracketsWeight = 0;

  /* Expected item */
  unsigned int expectedTerm = c_ExpectValue;

  /* Main parsing cycle */
  unsigned int pos = 0;
  while (pos < expression.length())
  {
    /* Storing root (we need it to clean allocated memory if exception will be occurred) */
    if (current)
      root = GetParent(current);

    /* Determine current character */
    const char curChar = pEquation[pos];
    
    /* It's a digit */
    if (IsDigit(curChar))
    {
      /* Unexpected term */
      if (expectedTerm != c_ExpectValue)
        throw Exception("Unexpected value. Expected term: " + GetTerm(expectedTerm));

      /* Extract number */
      unsigned int startPos = pos;
      while (IsDigit(pEquation[++pos]));

      /* May be number is real */
      if (pEquation[pos] == '.')
        while (IsDigit(pEquation[++pos]));
      string number = expression.substr(startPos, pos - startPos);

      /* New vertex creation */
      Vertex *newVertex = new Vertex();      
      newVertex->type = Equation::Number;
      newVertex->val  = atof(number.c_str());

      /* Where to place new node */
      switch (place)
      {
      case Equation::Here:
        current = newVertex;
        break;
      case Equation::Right:
        newVertex->weight = current->weight;
        VertexLink(newVertex, current, Equation::Right);      
        current = newVertex;
        break;
      }    

      /* Walking next */
      expectedTerm = c_ExpectOperator;
      continue;
    } /* Number */

    /* It's a operator */
    if (IsOperator(curChar))
    {
      /* Unexpected term */
      if (expectedTerm != c_ExpectOperator)
        throw Exception("Unexpected operator. Expected term: " + GetTerm(expectedTerm));

      /* Determine operator weight */
      unsigned int weight = GetOperatorWeight(curChar);

      /* Find place */
      current = VertexPlaceFind(current, weight + bracketsWeight);

      /* New node creation */
      Vertex *newVertex = new Vertex();      
      newVertex->type = Equation::BinaryOperator;
      newVertex->oper = GetOperatorType(curChar);
      newVertex->parent = current->parent;
      newVertex->weight = weight;

      /* Increase weight if there is parent vertex */
      if (current->parent)
        newVertex->weight += current->parent->weight;

      /* Moving already exist tree to the left subtree */
      VertexLink(current, newVertex, Equation::Left);
      current = newVertex;

      /* Recalculate priority at left subtree */
      UpdateWeight(newVertex->left, weight);
      place = Equation::Right;

      /* Walking next */
      expectedTerm = c_ExpectValue;
      pos++;
      continue;
    } /* Operator */

    /* It's a bracket */
    if (IsBracketRound(curChar))
    {
      /* What is the bracket */
      switch (curChar)
      {
      case c_BracketRoundOpen:
        bracketsWeight += c_WeightBracket;
        break;
      case c_BracketRoundClose:
        bracketsWeight -= c_WeightBracket;
        break;
      }

      /* Walking next */
      pos++;
      continue;
    } /* Bracket */

    /* It's a symbol */
    if (IsAlpha(curChar))
    {
      /* Unexpected term */
      if (expectedTerm != c_ExpectValue)
        throw Exception("Unexpected value. Expected term: " + GetTerm(expectedTerm));

      /* Extract number */
      unsigned int startPos = pos;
      while (IsAlpha(pEquation[++pos]));

      /* Term separation */
      string someWord = expression.substr(startPos, pos - startPos);

      /* New vertex creation */
      Vertex *newVertex = new Vertex();   
      newVertex->param = someWord;    

      /* Next expected value */
      expectedTerm = c_ExpectOperator;

      /* Where to place new node */
      switch (place)
      {
      case Equation::Here:
        current = newVertex;          
        break;
      case Equation::Right:
        newVertex->weight = current->weight;
        VertexLink(newVertex, current, Equation::Right);      
        current = newVertex;
        break;
      } /* Where to place */ 

      /* Is it constant */
      if (IsConstant(someWord))
      {
        /* New vertex creation */           
        newVertex->type  = Equation::Constant;
        newVertex->val   = GetConstantValue(someWord);  
      } else if (IsFunction(someWord))
      {
        /* New vertex creation */   
        newVertex->type   = Equation::Function;
        newVertex->func   = GetFunctionType(someWord);
        newVertex->weight = c_WeightFunc;

        /* Operand should be placed to right subtree */
        place = Equation::Right;
        expectedTerm = c_ExpectValue;
      } else if (IsVariable(someWord))
      {
        /* New vertex creation */           
        newVertex->type  = Equation::Variable;
        newVertex->param = someWord;
      } else /* It's a parameter */
        newVertex->type  = Equation::Parameter;  

      /* Walking next */
      continue;
    } /* Some function / constant / variable / parameter */

    /* Walk to next symbol */
    pos++;
  } /* End of main parsing cycle */

  /* Storing built tree pointer */
  if (current)
    root = GetParent(current);
} /* End of 'Equation::ParseEquation' method */