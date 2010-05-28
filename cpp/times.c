#include <unistd.h>
#include <sys/times.h>

void main (void)
{
    long clkFreq = sysconf(_SC_CLK_TCK);
    unsigned long x=1;
    int i;
    if (clkFreq == -1)
        printf("Error while reading the SC_CLK_TCK\n");
    else
        printf("the system clock frequency is: %d\n", clkFreq);

    printf("sizeof(long): %d\n", sizeof(long));
    printf("sizeof(clock_t): %d\n", sizeof(clock_t));
    printf("sizeof(tms): %d\n", sizeof(struct tms));

    
    for (i = 0; i<32; ++i)
        x = x | (0x1 << i);
    printf("%u", x);
    
}
