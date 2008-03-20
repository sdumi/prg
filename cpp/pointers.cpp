#include <iostream>
using namespace std;
class B;
class A
{
public:
  A()
  {
    cout << "A" << endl;
    aB = 0;
  }
  ~A() 
  {
    cout << "~A" << endl;
  }

  void doIt();
  B* aB;
};

class B
{
public:
  B()
  {
    cout << "B" << endl;
    aA = 0;
  }
  ~B()
  {
    cout << "~B" << endl;
  }
  void start();
  void deleteTheA();

  A* aA;
};

int main()
{
  B b;
  b.start();
  return 0; 
}

void A::doIt()
{
  cout << "A::doIt" << endl;
  if (aB)
    {
      aB->deleteTheA();
    }
  cout << "exit: A::doIt" << endl;
}

void B::start()
{
  cout << "B::start" << endl;
  aA = new A();
  aA->aB = this;
  aA->doIt();
  cout << "exit: B::start" << endl;
}

void B::deleteTheA()
{
  cout << "B::deleteTheA" << endl;
  if (aA)
    {
      delete aA;
    }
  cout << "exit: B::deleteTheA" << endl;
}
