#include <stdio.h>

#include <Foundation/Foundation.h>

/**
 * class Test that implements the class method (classStringValue)
 */
@interface Test
+ (const char*) classStringValue;
@end

/**
 * define the Test class and the class method (classStringValue)
 */
@implementation Test
+ (const char*) classStringValue;
{
    return "This is the string value of the Test class";
}
@end

/**
 * the main() function: pass a message to the Test class
 */
int main(void)
{
    printf("%s\n", [Test classStringValue]);
    return 0;
}

