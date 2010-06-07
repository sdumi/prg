#include <iostream>
using namespace std;

struct baseFunctor
{
  template <class T>
  bool operator()(const T& s1, const T& s2)
  {
    cout << "inside baseFunctor" << endl;
    return s1 < s2;
  }
};

struct secondFunctor
{
  template <class T>
  bool operator()(const T& s1, const T& s2)
  {
    if (s1 == 1) {
      cout << "s1 == 1" << endl;
      return true;
    }
    baseFunctor b;
    return b(s1, s2);
  }
};

int main(void)
{
  cout << "HelloWorld" <<endl;
  baseFunctor b;
  secondFunctor s;
  if (b(1,2) && s(1,2)) {
    cout << "1<2" << endl;
  }
  return 0;
}
