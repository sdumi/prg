#include <iostream>
using namespace std;

class A
{
public:
  virtual void f()
    {
      cout << "A::f()" << endl;
    }
  void g()
    {
      cout << "A::g()" << endl;
    }
};

class B: public A
{
public:
  void f()
    {
      cout << "B::f()" << endl;
    }
  void g()
    {
      cout << "B::g()" << endl;
    }
};

class C: public B
{
public:
  void f()
    {
      cout << "C::f()" << endl;
    }
  void g()
    {
      cout << "C::g()" << endl;
    }
};

int main(void)
{
  C c;
  B b;
  A *pa = &b;
  pa->f();
  pa->g();
  pa = &c;
  pa->f();
  pa->g();

  B* pb = &c;
  pb->f();
  pb->g();

  B& br(c);
  b = c;
  b.f();
  b.g();
  br.f();
  br.g();
}
