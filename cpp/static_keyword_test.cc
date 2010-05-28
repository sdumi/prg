#include <iostream>
using namespace std;

class A
{
public:

  void getNext()
    {
      static int  idx = 0;
      cout << idx++ << endl;
    }
};



int main(void)
{
  A a1, a2;
  a1.getNext();
  a1.getNext();
  a1.getNext();

  a2.getNext();
  a1.getNext();

  a2.getNext();
  a1.getNext();

  return 0;
}
