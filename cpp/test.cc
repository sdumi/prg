#include <iostream>
using namespace std;

class A
{

public:
  void show()
    {
      cout <<"A::show";
    }
};

class B: protected A
{
public:
  void show()
    {
      cout <<"B::show";
    }

};

int main()
{
  B b;
  b.show();
}



/*
void f()
{
  int n = 0;
  if (n == 1)
    throw "1";
  if (n == 2)
    throw 2;
}

int main()
{
  try
  {
    f();
  }
  catch (int i){
    cout << "int";
    return 2;
  }
  catch (const char* cp){
    cout << "char";
    return 3;
  }
  catch(...)
  {
    cout << "...";
    return 1;
  }
    cout << "nada";
}
*/
