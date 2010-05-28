#include <iostream>
using namespace std;

int main(void)
{

  {
    int a=0, b=1, c=2, d=3;
    cout << "a)" << endl;

    cout << "a = " << a << " b = " << b << " c = " << c << " d = " << d << endl;

    a = b++, c++, d++;
    cout << "a = " << a << " b = " << b << " c = " << c << " d = " << d << endl;
    cout << "-----------------------" << endl;
  }
  {
    cout << "b)" << endl;
    int a=0, b=1, c=2, d=3;
    cout << "a = " << a << " b = " << b << " c = " << c << " d = " << d << endl;

    a = (b++, c++, d++);
    cout << "a = " << a << " b = " << b << " c = " << c << " d = " << d << endl;
    cout << "-----------------------" << endl;
  }
  {
    cout << "c)" << endl;
    int a=0, b=1, c=2, d=3;
    cout << "a = " << a << " b = " << b << " c = " << c << " d = " << d << endl;

    a = (d++);
    cout << "a = " << a << " b = " << b << " c = " << c << " d = " << d << endl;
    cout << "-----------------------" << endl;
  }
}


