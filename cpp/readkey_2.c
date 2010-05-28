#include <stdio.h>
#include <termios.h>
#include <unistd.h>
/**
 * this program will wait for a key to be pressed and then will print "Hello World!"
 * special keys (shift, ctrl, alt, capslock) are not treated.
 */
int main(void)
{
    struct termios to, t;

    tcgetattr(1, &t);/* get the current terminal attributes*/
    to = t; /*copy the original attr*/
    t.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(1, 0, &t);
    char c;
    
    if (c = getchar())
    {
        printf("Hello World!\n%c \n", c);
    }
    tcsetattr(1, 0, &to);/*restore the attributes*/
    
    return 0;
}
