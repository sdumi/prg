
/* $Id: bfo.c,v 1.9 2000/05/18 21:34:50 panu Exp $
 *
 * This file is subject to the license described in the file "LICENSE" */

/* Compiler optimisation routines */

#include <stdio.h>
#include <stdlib.h>
#include "bfc.h"

void bfo1( tok *first ) /* Remove identical sequential cmds */
{
      tok *n = first;
      if ( n->n ) n = n->n;
      while ( n->n ) {
	    tok *nn = n->n;
	    if ( n->type == nn->type && n->offs == nn->offs &&
		 n->ref_offs == nn->ref_offs && !n->c ) {
		  n->times += nn->times;
		  n->n = nn->n;
		  free( nn );
		  continue;
	    }
	    if ( !nn->times && !nn->c ) {
		  n->n = nn->n;
		  free( nn );
		  continue;
	    }
	    n = nn;
      }
}

void bfo2( tok *first ) /* Remove vain moves & nops */
{
      tok *n = first;
      int offs = 0;
      while ( n->n ) {
	    tok *nn = n->n;
	    if ( nn->c && offs ) {
		  if ( nn->type != T_NOP && nn->type != T_MOV ) {
			nn = get_tok();
			nn->n = n->n;
			n->n = nn;
			n = nn;
		  }
		  nn->type = T_MOV;
		  nn->times += offs;
		  offs = 0;
		  n = n->n;
		  continue;
	    }
	    if ( nn->c ) {
		  n = nn;
		  continue;
	    }
	    if ( nn->type == T_MOV ) {
		  offs += nn->times;
		  n->n = nn->n;
		  free( nn );
		  continue;
	    }
	    if ( nn->type == T_NOP ) {
		  n->n = nn->n;
		  free( nn );
		  continue;
	    }
	    nn->offs += offs;
	    nn->ref_offs += offs;
	    n = nn;
      }
      first->offs += offs;
}

void bfo3( tok *first ) /* Sort by offset */
{
      tok *n = first;
      tok *blk = first;
      int offs = SMALL;
      while ( n->n ) {
	    tok *nn = n->n;
	    if ( ( nn->type != T_INC && nn->type != T_SET ) ||
		 ( nn->type == T_SET && nn->offs != nn->ref_offs ) ) {
		  blk = nn; /* Found sort block boundary */
		  n = nn;
		  offs = SMALL;
		  continue;
	    }
	    if ( nn->offs < offs ) {
		  n->n = nn->n; /* Remove */
		  n = blk;
		  while( n->n->offs <= nn->offs ) n = n->n;
		  nn->n = n->n; /* And put where it belongs */
		  n->n = nn;
	    }
	    offs = nn->offs;
	    n = nn;
      }
}

void bfo4_2( tok *n, tok **wrp, int incr ) /* Alter type */
{
      switch ( n->type ) {
      case T_INC:
	    if ( n->offs ) {
		  n->type = T_ADD;
		  n->times *= -incr;
		  n->ref_offs = 0;
		  n->n = (*wrp)->n;
		  (*wrp)->n = n;
		  *wrp = n;
		  break;
	    } /* Fallthru */
      default:
	    free( n );
	    break;
      case T_SET:
	    n->ref_offs = 0;
	    n->n = (*wrp)->n;
	    (*wrp)->n = n;
	    *wrp = n;
      }
}

void bfo4_1( tok *parent ) /* Check if loop removal is OK */
{
      tok *n = parent->c; 
      int i, incr = 0, set[OPT_ARR_SIZ], inc[OPT_ARR_SIZ];
      for ( i = 0; i < OPT_ARR_SIZ; i++ ) inc[i] = set[i] = 0;
      if ( n->offs ) return; /* Moving loop */
      while ( n ) {
	    if ( n->c ) return; /* Nested loop */
	    if ( n->type != T_INC && n->type != T_SET && n->type != T_NOP )
		  return; /* Bad types (T_ADD -> T_MUL? ha.) */
	    if ( n->type == T_INC ) inc[n->offs + OPT_ARR_SIZ/2] = 1;
	    if ( n->type == T_SET ) set[n->offs + OPT_ARR_SIZ/2] = 1;
	    if ( n->type == T_INC && !n->offs ) incr += n->times;
	    n = n->n;
      }
      if ( incr != -1 && incr != 1 ) return; /* Unclear end-condition */
      for ( i = 0; i < OPT_ARR_SIZ; i++ )
	    if ( inc[i] && set[i] ) return; 
		/* Unclear behavior, bfo5() would eliminate trivial */

      n = parent->c; /* removal OK, go through the loop instructions */
      parent->c = NULL;
      while ( n ) {
	    tok *nn = n->n;
	    bfo4_2( n, &parent, incr );
	    n = nn;
      }
      n = get_tok();
      n->type = T_SET;
      n->n = parent->n;
      parent->n = n;
}

void bfo4( tok *first ) /* Open rep. blocks */
{
      tok *n = first;
      while ( n->n ) {
	    tok *nn = n->n;
	    if ( nn->c ) bfo4_1( nn );
	    n = nn;
      }
}

void bfo5( tok *first ) /* Combine SET+INC */
{
      tok *n = first;
      while ( n->n ) {
	    tok *nn = n->n;
	    if ( ( n->type == T_SET || n->type == T_INC ) && !nn->c &&
		 n->offs == nn->offs && n->ref_offs == nn->ref_offs ) {
		  if ( nn->type == T_SET ) {
			n->type = T_SET;
			n->value = nn->value;
			n->n = nn->n;
			free( nn );
			continue;
		  }
		  if ( nn->type == T_INC ) {
			n->value += nn->times;
			n->n = nn->n;
			free( nn );
			continue;
		  }
	    }
	    n = nn;
      }
}

