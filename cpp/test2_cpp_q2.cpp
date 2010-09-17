#include <iostream>
using namespace std;

class A
{
public:
  void show()
    {cout<<"A::show"<<endl;}
};
class B: protected A
{
public:
  void show()
    {
      cout << "B::show" << endl;
    }
};

struct AA
{
protected:
  int b;
private:
  int c;
};


int main()
{
  B b;
  b.show();
  AA a;
  a.b = 3;

}
