#include <iostream>
#include <unistd.h>
using namespace std;

int main(void)
{
  cout << sbrk(0) << endl;
  int *p = new int(0);
  cout << "value of my dynamic pointer: " << *p << endl;

  cout << sbrk(0) << endl;
  delete p;

  return 0;
}
