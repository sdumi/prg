#include <iostream>
using namespace std;

class A
{
public:
  A()
    {
      cout << "A::A()" << endl;
      _nr = 0;
    }
  A(int nr)
    {
      cout << "A::A(int)" << endl;
      _nr = nr;
    }
  int getValue() const
    {
//      cout << "A::getValue" << endl;
      return _nr;
    }
  A& operator=(A& a)
    {
      cout << "A::operator=(A&)" << endl;
      _nr = a.getValue();
      return *this;
    }
  A& operator=(A a)
    {
      cout << "A::operator=(A)" << endl;
      _nr = a.getValue();
      return *this;
    }
  A operator++(int)
    {
      cout << "A::operator++(A&)" << endl;
      A tmp=*this;

      _nr = _nr+1;
      return tmp;
    }

private:
  int _nr;
};

ostream& operator<< (ostream& ostr, const A& a)
{
  ostr << a.getValue();
  return ostr;
}



int main(void)
{
  int x = 1;
  int y = 5;

//   cout << "x == " << x << "; y = " << y << endl;
//   y = x++;
//   cout << "x == " << x << "; y = " << y << endl;
//   x = x++;
//   cout << "x == " << x << "; y = " << y << endl;

  A a(5);
  A b(2);

  a=a++;
  cout << "a == " << a << endl << "b == " << b << endl;

  return 0;
}
