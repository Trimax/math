/*           FILE: simplify.cpp
 *           DATE: 22 Sep 2010 ã.
 *         AUTHOR: Eliseev Dmitry
 *        PROJECT: mathkernel
 *    LAST UPDATE: Updated on 22.09.2010
 *           NOTE: Simplify method implementation
 *
 * CONTACT PERSON: Eliseev Dmitry
 */

/* System modules including */

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
 * FUNCTION: Simplify equation's tree
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
void Equation::Simplify( void )
{
  /* There is no equation */
  if (!root)
    return;

  /* Starting simplify */
  SimplifySubtree(root);
} /* End of 'Equation::Simplify' method */

/***
 * FUNCTION: Simplify subtree
 *    PARAM: [IN] tree - pointer to subtree root
 *      SEE: write me
 *   AUTHOR: Eliseev Dmitry
 ***/
void Equation::SimplifySubtree( Equation::Vertex *tree )
{
  /* Reset calculable flag */
  tree->isCalculable = false;

  /* What is the vertex? */
  switch(tree->type)
  {
    /* Nothing to simplify */
  case Number:
  case Constant:
    tree->isCalculable = true;
    break;

    /* Parameter was set */
  case Parameter:
    tree->isCalculable = tree->isSet;
    break;

    /* Variable */
  case Function:
    SimplifySubtree(tree->right);
    if (tree->right->isCalculable)
    {
      /* Update value */
      tree->val = Calculate(tree, 0.0);

      /* Remove calculated subtree */
      RemoveSubtree(tree->right);
      tree->right = NULL;

      /* Update vertex type */
      tree->type = Number;
      tree->isCalculable = true;

      /* Storing weight */
      if (tree->parent)
        tree->weight = tree->parent->weight;
    }
    break;

    /* Binary operator */
  case BinaryOperator:
    /* Simplify both subtrees */
    SimplifySubtree(tree->left);
    SimplifySubtree(tree->right);

    /* Both subtrees are calculable */
    if (tree->left->isCalculable && tree->right->isCalculable)
    {
      tree->val = Calculate(tree, 0.0);

      /* Remove calculated subtrees */
      RemoveSubtree(tree->left);
      RemoveSubtree(tree->right);
      tree->left = NULL;
      tree->right = NULL;

      /* Update vertex type */
      tree->type = Number;
      tree->isCalculable = true;

      /* Storing weight */
      if (tree->parent)
        tree->weight = tree->parent->weight;
    }
    break;
  }
} /* End of 'Equation::SimplifySubtree' method */