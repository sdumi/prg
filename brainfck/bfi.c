#include <stdio.h>

int  p, r, q;
char a[5000], f[5000], b, o, *s=f;

void interpret(char *c)
{
	char *d; int tmp;

	r++;
	while( *c ) {
	      //if(strchr("<>+-,.[]\n",*c))printf("%c",*c);
	      switch(o=1,*c++) {
	      case '<': p--;        break;
	      case '>': p++;        break;
	      case '+': a[p]++;     break;
	      case '-': a[p]--;     break;
	      case '.': putchar(a[p]); fflush(stdout); break;
	      case ',': 
		    tmp=getchar();
		    if (tmp == EOF) a[p]=0; 
		    else a[p]=tmp;
		    break;
	      case '[':
			for( b=1,d=c; b && *c; c++ )
				b+=*c=='[', b-=*c==']';
			if(!b) {
				c[-1]=0;
				while( a[p] )
					interpret(d);
				c[-1]=']';
				break;
			}
		case ']':
			puts("UNBALANCED BRACKETS"), exit(0);

		default: o=0;
		}
		if( p<0 || p>100)
			puts("RANGE ERROR"), exit(0);
	}
	r--;
}

int main(int argc,char *argv[])
{
	FILE *z;

	q=argc;

//	if((z=fopen(argv[1],"r"))) {
//		while( (b=getc())>0 )
//	if((z=fopen(stdin,"r"))) {
		while( (b=getc(stdin))>0 )
			*s++=b;
		*s=0;
		interpret(f);
//	}
	return 0;
}

