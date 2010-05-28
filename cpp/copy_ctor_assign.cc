#include <iostream>
using namespace std;

class Foo
{
public:
  Foo() { cout << "Foo::Foo()" << endl << endl; }
  Foo& operator=(const Foo&) { cout << "Foo::operator=(const Foo&)" << endl << endl;}
private:
  Foo(const Foo& b) { *this = b; cout << "Foo::Foo(const Foo&)" << endl << endl; }
};

int main()
{
  Foo foo;
  foo = Foo();
}
