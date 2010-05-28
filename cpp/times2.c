#include <stdio.h>
#include <time.h>

int main(void)
{
    struct timespec tp;
    printf("Print sizeof some basic types: \n");
    printf("sizeof(int)\t=%d\n", sizeof(int));
    printf("sizeof(long)\t=%d\n", sizeof(long));
    printf("sizeof(time_t)\t=%d\n", sizeof(time_t));
    printf("\n");
    {
        printf("get the time using clock_gettime(CLOCK_REALTIME,...)\n");
        
        if (clock_gettime(CLOCK_REALTIME, &tp) == 0)
        {
            printf("seconds \t=%d\n", tp.tv_sec);
            printf("nanoseconds \t=%d\n", tp.tv_nsec);
        }
        else
        {
            printf("error while during clock_gettime(CLOCK_REALTIME, ...) call\n");
        }
    }
    {
        printf("get the time using clock_gettime(CLOCK_MONOTONIC,...)\n");
        
        if (clock_gettime(CLOCK_MONOTONIC, &tp) == 0)
        {
            printf("seconds \t=%d\n", tp.tv_sec);
            printf("nanoseconds \t=%d\n", tp.tv_nsec);
        }
        else
        {
            printf("error while during clock_gettime(CLOCK_MONOTONIC, ...) call\n");
        }
    }
    
    
    return 0;
}
