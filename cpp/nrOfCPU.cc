#include <unistd.h>
#include <iostream>
using namespace std;

int main (void)
{
  cout << "Nr of CPUs online: " << sysconf(_SC_NPROCESSORS_ONLN) << endl;
  cout << "Nr of CPUs configured: " << sysconf(_SC_NPROCESSORS_CONF) << endl;
  return 0;
}
