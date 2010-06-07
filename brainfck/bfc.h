
/* $Id: bfc.h,v 1.3 2000/05/11 13:31:15 panu Exp $
 *
 * This file is subject to the license described in the file "LICENSE" */

#ifndef __bfc_bfc_h__
#define __bfc_bfc_h__

#define SMALL -20000
#define BIG 20000
#define OPT_ARR_SIZ 100

enum type {
      T_NOP,
      T_INC,
      T_MOV,
      T_INP,
      T_OUP,
      T_SET,
      T_ADD
};

typedef struct tok {
      int type;
      int times;
      int offs;
      int ref_offs;
      int value;
      struct tok *c;
      struct tok *n;
} tok;

//extern tok *queue;

void bft( tok *first );
tok *get_tok(void);
void bforec( tok *first, void(*func)(tok*) );
void dumplist( tok *first, int ind );
void indent( int ind );
void bfo1( tok *first ); /* Remove identical sequential cmds */
void bfo2( tok *first ); /* Remove vain MOV+NOP */
void bfo3( tok *first ); /* Sort by offset */
void bfo4( tok *first ); /* Open rep. blocks */
void bfo5( tok *first ); /* Combine SET+INC */

#endif
