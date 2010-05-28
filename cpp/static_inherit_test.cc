#include <iostream>
using namespace std;

class A
{
public:
  static void f() { cout << "A::f()" << endl; }
  static void g() { cout << "A::g()" << endl; }
};

class B: public A
{
public:
  static void f() { cout << "B::f()" << endl; }
};

class C
{
public:
  void r()
    {
      cout << "C::r()"<<endl;
      B::f();
    }
};

int main(void)
{
  A a, *pa, *pva;
  B b, *pb;

  A::f();
  A::g();
  B::f();
  B::g();

  cout << "-----------------------------" << endl;
  cout << "-----------------------------" << endl;
  C c;
  c.r();

  return 0;
}
