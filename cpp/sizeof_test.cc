#include <iostream>
using namespace std;

class A
{
public:

  int i;
  virtual int print(int i)
    {cout << i;}
  virtual ~A()
    {}


};

class B: public virtual A
{
public:

  B()
    {i =  3;}
  virtual ~B()
    {}

  char c;
  char d;
  char e;
  char f;
  char g;
  virtual int print (int i)
    {}
  virtual void hellot()
    {}

};


int main(void)
{
  cout << "sizeof(A): " << sizeof(A) << endl;
  cout << "sizeof(B): " << sizeof(B) << endl;
  cout << "sizeof(word): " << sizeof(unsigned short) << endl;
  cout << "sizeof(uchar): " << sizeof(unsigned char) << endl;
  cout << "sizeof(ulong): " << sizeof(unsigned long) << endl;
  return 0;
}
