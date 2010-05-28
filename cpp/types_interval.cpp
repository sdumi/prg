#include <iostream>
#include <stdio.h>
using namespace std;

int main(void)
{
  cout << "sizeof (long long) = " << sizeof(long long) << endl;
  cout << "sizeof (long)      = " << sizeof(long) << endl;
  cout << "sizeof (double)    = " << sizeof(double) << endl;

  cout << "sizeof (unsigned long long) = " << sizeof(unsigned long long) << endl;


  long long x = 0;
  cout << "sizeof (x)         = " << sizeof(x) << endl;
  cout << "x == " << x << endl;


  x = 0xFFFFFFFF;
  x = x << 32;
  x |= 0xFFFFFFFF;
  cout << "x == " << x << endl;


  double a = x, b= x;
   cout << "a == " << a << endl;
   cout << "b == " << b << endl;
   a = a+1;
   cout << "a == " << a << endl;
   cout << "a-x ==" << a-x <<endl;
   cout << "a-b ==" << a-b <<endl;

   x = x+1;
  cout << "x == " << x << endl;

  return 0;
}
