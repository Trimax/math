/*           FILE: vertex.cpp
 *           DATE: 18 Sep 2010 ã.
 *         AUTHOR: Eliseev Dmitry
 *        PROJECT: mathkernel
 *    LAST UPDATE: Updated on 18.09.2010
 *           NOTE: Vertex class implementation
 *
 * CONTACT PERSON: Eliseev Dmitry
 */

/* System modules including */
#include <iostream>
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
 * FUNCTION: Links two vertices's
 *    PARAM: [IN] children - pointer to child vertex
 *    PARAM: [IN] parent   - pointer to parent
 *    PARAM: [IN] place    - place to add
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
void Equation::VertexLink( Equation::Vertex *children, Equation::Vertex *parent, const VertexPlace place )
{
  /* Storing parent pointer */
  children->parent = parent;

  /* Store old parent pointer */
  VertexChange(parent->parent, children, parent);
 
  /* Storing pointer */
  switch(place)
  {
  case Equation::Left:
    parent->left = children;    
    break;
  case Equation::Right:
    parent->right = children;
    break;
  }
} /* End of 'VertexAdd' function */

/***
 * FUNCTION: Find place to add new vertex by operator's weight
 *   RETURN: Pointer to vertex in tree to replace it with operator
 *    PARAM: [IN] current - pointer to current vertex
 *    PARAM: [IN] weight  - operator weight
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
Equation::Vertex* Equation::VertexPlaceFind( Vertex *current, const unsigned int weight ) const
{
  Vertex *cur = current;

  /* Moving up by branch while position will not found */
  while ((cur->parent)&&(weight <= cur->parent->weight))
    cur = cur->parent;

  /* That's it */
  return cur;
} /* End of 'Equation::VertexPlaceFind' method */

/***
 * FUNCTION: Update subtree and set new priority
 *   RETURN: Pointer to subtree root
 *    PARAM: [IN] current - pointer to subtree root
 *    PARAM: [IN] weight  - operator weight
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
void Equation::UpdateWeight( Vertex *current, const unsigned int weight )
{
  /* There is no tree */
  if (!current)
    return;

  stack<Vertex*> verticesStack;
  verticesStack.push(current);

  /* Walking tree */
  while (!verticesStack.empty())
  {
    Vertex *cur = verticesStack.top();
    verticesStack.pop();

    /* Update priority */
    cur->weight += weight;

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
  } /* End of while */
} /* End of 'Equation::UpdateWeight' method */

/***
 * FUNCTION: Prints to console built subtree
 *    PARAM: [IN] current    - pointer to subtree root
 *    PARAM: [IN] currentTab - current tabulation
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
void Equation::PrintSubTree( const Vertex *current, const unsigned int currentTab )
{
  /* Wrong pointer */
  if (!current)
    return;

  /* Output spaces */
  unsigned int curSpace = 0;
  for (curSpace = 0; curSpace < currentTab; curSpace++)
    cout << " ";

  /* Process vertex */
  switch(current->type)
  {
  case Equation::Number:
    cout << current->val <<  endl;
    break;
  case Equation::Constant:
    cout << current->param << endl;
    break;
  case Equation::Parameter:
    cout << current->param << endl;
    break;
  case Equation::Variable:
    cout << current->param << endl;
    break;
  case Equation::UnaryOperator:
    break;
  case Equation::Function:
    cout << current->param << endl;
    PrintSubTree(current->right, currentTab+2);
    break;
  case Equation::BinaryOperator:
    cout << GetOperatorSymbol(current->oper) << endl;
    PrintSubTree(current->left, currentTab+2);
    PrintSubTree(current->right, currentTab+2);
    break;
  } /* End of switching vertex type */
} /* End of 'Equation::PrintSubTree' method */

/***
 * FUNCTION: Links two vertices's
 *    PARAM: [IN] parent   - pointer to parent vertex
 *    PARAM: [IN] oldChild - pointer to old vertex
 *    PARAM: [IN] newChild - pointer to new vertex
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
void Equation::VertexChange( Vertex *parent, Vertex *oldChild, Vertex *newChild )
{
  if (!parent)
    return;

  /* What is the vertex */
  switch (parent->type)
  {
  case Equation::BinaryOperator:
    if (parent->left == oldChild)
      parent->left = newChild;
    else
      parent->right = newChild;
    break;
  case Equation::Function:
    parent->right = newChild;
    break;
  default:
    parent->left = newChild;
  } /* End of switch */
} /* End of 'Equation::VertexChange' method */

/***
 * FUNCTION: Moving to parent from current vertex
 *   RETURN: Pointer to tree's root
 *    PARAM: [IN] current - pointer to current vertex
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
Equation::Vertex* Equation::GetParent( Vertex *current ) const
{
  Vertex *cur = current;
  while (cur->parent)
    cur = cur->parent;
  return cur;
} /* End of 'Equation::GetParent' method */