#include <stdio.h>
#include <unistd.h>

int main()
{
    FILE* stream = popen ("arch", "r");
    char s[100];
    
    fscanf (stream, "%s", s);
    printf ("arch a spus ca suntem: %s\n", s);
    
    
    /*     fprintf (stream, "This is a test.\n"); */
    /*     fprintf (stream, "hello\n"); */
    return pclose(stream);
}
