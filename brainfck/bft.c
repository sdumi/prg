
/* $Id: bft.c,v 1.5 2000/07/19 18:24:48 panu Exp $
 *
 * This file is subject to the license described in the file "LICENSE" */

/* Routines for reading the program in */

#include <stdio.h>
#include <stdlib.h>
#include "bfc.h"

tok *get_tok(void)
{
      tok *res = malloc( sizeof(tok) );
      res->type = T_NOP;
      res->n = NULL;
      res->times = 1;
      res->offs = 0;
      res->value = 0;
      res->ref_offs = 0;
      res->c = NULL;
      return res;
}

void bft( tok *first )
{
      int tmp;
      tok *last = first;

      while (( tmp = getchar() ) != EOF ) {
	    if ( tmp == ']' ) break;
	    last->n = get_tok();
	    switch ( tmp ) {
	    case '-':
		  last->n->times = -1;
		  /* Fallthrough */
	    case '+':
		  last->n->type = T_INC;
		  break;
	    case '<':
		  last->n->times = -1;
		  /* Fallthrough */
	    case '>':
		  last->n->type = T_MOV;
		  break;
	    case '[':
		  last->n->c = get_tok();
		  last->n->times = 0;
		  bft( last->n->c );
		  break;
	    case ',':
		  last->n->type = T_INP;
		  break;
	    case '.':
		  last->n->type = T_OUP;
		  break;
	    default:
		  free( last->n );
		  last->n = NULL;
		  continue;
	    }
	    last = last->n;
      }
}
