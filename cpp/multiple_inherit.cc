#include <iostream>
using namespace std;
class B
{
public:
  B()
    {
      cout << "B()"<<endl;
    }
  long int  b[1024];
};


class A10: public virtual B
{
public:
    A10() { cout << "A10()"<<endl; }
};

class A11: public virtual B
{
public:
  A11() { cout << "A11()"<<endl; }
  long int  a11[1024];
};

class A12: public virtual B
{
public:
  A12() { cout << "A12()"<<endl; }
};

class A13: public virtual B
{
public:
  A13() { cout << "A13()"<<endl; }
};

class A14: public virtual B
{
public:
  A14() { cout << "A14()"<<endl; }
};

class A15: public virtual B
{
public:
  A15() { cout << "A15()"<<endl; }
};

class A16: public virtual B
{
public:
  A16() { cout << "A16()"<<endl; }
};

class A17: public virtual B
{
public:
  A17() { cout << "A17()"<<endl; }
};

class A18: public virtual B
{
public:
  A18() { cout << "A18()"<<endl; }
};

class A19: public virtual B
{
public:
  A19() { cout << "A19()"<<endl; }
};

class A20: public virtual B
{
public:
  A20() { cout << "A20()"<<endl; }
};

class A21: public virtual B
{
public:
  A21() { cout << "A21()"<<endl; }
};

class A22: public virtual B
{
public:
  A22() { cout << "A22()"<<endl; }
};

class Test: public virtual B, public virtual A10, public virtual A11, public virtual A12, public virtual A13, public virtual A14, public virtual A15, public virtual A16, public virtual A17, public virtual A18, public virtual A19, public virtual A20, public virtual A21, public virtual A22
{
public:
  Test()  { cout << "Test()" << endl; }
};


int main(void)
{
  Test t, t1;
  cout << "sizeof(t): "<<sizeof(t)<<endl;

}
