#include <iostream>
using namespace std;
class A {
public:
  void sshow()
    {}

};
class B : protected A {
public:
  void show()
    {}

 };
int main()
{
   B b;
   b.sshow();
}
