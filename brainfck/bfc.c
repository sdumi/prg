
/* $Id: bfc.c,v 1.9 2000/05/11 13:31:15 panu Exp $
 *
 * This file is subject to the license described in the file "LICENSE" */

/* Compiler general routines */

#include <stdio.h>
#include "bfc.h"

static char *toknames[] = {
      "Nop    ",
      "Inc    ",
      "Move   ",
      "Input  ",
      "Output ",
      "Set    ",
      "Add    ",
      NULL
};

static tok *queue;

void bforec( tok *first, void(*func)(tok*) )
{
      tok *n = first;
      while ( n ) {
	    if ( n->c ) bforec( n->c, func );
	    n = n->n;
      }
      func( first );
}

void dumpprog_1( tok *first )
{
      tok *n = first;
      while ( n ) {
	    switch ( n->type ) {
	    case T_INC:
		  printf( "a[p+%d]+=%d;", n->offs, n->times );
		  break;
	    case T_MOV:
		  printf( "p+=%d;", n->times );
		  break;
	    case T_INP:
		  printf( "for(i=0;i<%d;i++)", n->times ); /* Stupid */
		  printf( "{a[p+%d]=getchar();if(a[p+%d]==EOF)a[p+%d]=0;}",
			  n->offs, n->offs, n->offs );
		  break;
	    case T_OUP:
		  printf( "for(i=0;i<%d;i++)", n->times );
		  printf( "{putchar(a[p+%d]);fflush(stdout);}", n->offs );
		  break;
	    case T_SET:
		  if ( n->ref_offs != n->offs )
			printf( "if(a[p+%d])", n->ref_offs );
		  printf( "a[p+%d]=%d;", n->offs, n->value );
		  break;
	    case T_ADD:
		  printf( "a[p+%d]+=a[p+%d]*%d;", n->offs, 
			  n->ref_offs, n->times );
		  break;
	    }
	    if ( n->c ) {
		  printf( "for(;a[p];p+=%d){", n->c->offs );
		  dumpprog_1( n->c );
		  printf( "}" );
	    }
	    n = n->n;
      }
}

void dumpprog( tok *first )
{
      puts( "#include<stdio.h>\n#include<stdlib.h>\nlong *a;" );
      puts( "int p=8000,i;int main(void){a=calloc(16000,sizeof(long));" );
      dumpprog_1( first );
      puts( "return 0;}\n" );
}

void dumplist( tok *first, int ind )
{
      tok *n = first;
      indent( ind );
      fprintf( stderr, "{---\n" );
      while ( n ) {
	    indent( ind );
	    if ( n->type == T_SET ) {
		  fprintf( stderr, "%s@%d,%d",
			   toknames[n->type], n->offs, n->value );
		  if ( n->offs != n->ref_offs )
			fprintf( stderr, "(if@%d)", n->ref_offs );
	    } else {
		  fprintf( stderr, "%s@%d,%d", 
			   toknames[n->type], n->offs, n->times );
		  if ( n->type == T_ADD ) 
			fprintf( stderr, "*@%d", n->ref_offs );
	    }
	    putc( '\n', stderr );
	    if ( n->c ) dumplist( n->c, ind + 1 );
	    n = n->n;
      }
      indent( ind );
      fprintf( stderr, "---}\n" );
}

void indent( int ind )
{
      while ( ind-- ) putc( '\t', stderr );
}

void (*optimisations[])(tok*) = {
      bfo1, bfo2, bfo3, bfo1,	/* Remove repetition */
      bfo4, bfo2, bfo3, bfo5,	/* Remove loops #1 */
      bfo4, bfo2, bfo3, bfo5,	/* Remove loops #2 */
      bfo1, NULL		/* Clean */
};

int main( void ) {
      int i = 0;
      queue = get_tok();
      bft( queue );
      while ( optimisations[i] ) {
	    bforec( queue, optimisations[i] );
	    fprintf( stderr, "---- START OF DEBUG OUTPUT %d ----\n", i );
	    dumplist( queue, 1 );
	    fputs( "\n\n", stderr );
	    i++;
      }
      dumpprog( queue );
      fflush( stdout );
      return 0;
}

