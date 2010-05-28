#include <iostream>
using namespace std;

enum E_Test{
  e_a=1,
  e_b=2,
  e_c=1
};

int main(void)
{
  E_Test test = e_a;
  cout << test << endl;
  test = e_b;
  cout << test << endl;
  test = e_c;
  cout << test << endl;
  return 0;
}

