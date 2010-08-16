#include <stdio.h>
int main(void)
{
    int n = 5;
    printf("n = %d\n", n);
    n = (2+2)?:n-2;
    printf("n = %d\n", n);
    n = (2-2)?:n-2;    
    printf("n = %d\n", n);
    return 0;
}
