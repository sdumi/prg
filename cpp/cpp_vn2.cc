#include <iostream>
using namespace std;

class Base
{
public:
  Base()
    {
      cout<<"Base ctor"<<endl;
    }
  virtual ~Base()
    {
      cout <<"~Base"<<endl;
    }
};
class SubClass:public Base
{};

int main()
{
  SubClass *psc1 = new SubClass();
  SubClass *psc2 = new SubClass();
  SubClass **vsc = {psc1, psc2};
//  Base **pb = &vsc[0];
  delete []vsc;


  return 0;
}

// class X
// {
// public:
//   X()
//     {
//       cout << "normal ctor"<<endl;

//     }
//   X(int j)
//     :n(j)
//     {cout << "int ctor" << endl;

//     }
//   X(const X& rhs)
//     {
//       cout << "copy ctor" << endl;

//       this->n = rhs.n+1;
//     }

//   const X& operator=(const X& rhs)
//     {
//       cout << "operator=" << endl;

//       this->n = rhs.n + 2;
//       return *this;
//     }
// public:
//   int n;
// };

// int main()
// {
//   X x1(0);
//   X x2(x1);
//   X x3=x2;

//   cout << x3.n << endl;
//   return 0;

// }


// class A
// {
// public:
//   void show()
//     {
//       cout<<"A::show()";
//     }
// };

// class B: protected A
// {
// public:
//   void show()
//     {
//       cout << "B::show()";
//     }
// };

// int main()
// {
//   B b;
//   b.show();
//   return 0;

// }
