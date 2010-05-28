#include <iostream>
using namespace std;

template <typename T,
          int value>
class Test
{
public:
  Test();
  template <typename X> void printMe(X);
//  void printMe(char);

};

int main()
{
  cout <<"Hello" << endl;
  Test<char, 4> test;

  test.printMe('a');

}

template<typename T,
         int value>
Test<T, value>
::Test()
{
  cout <<"here in constructor: " << value << endl;
}

template<typename T,
         int value> template <typename X>
void
Test<T, value>
::printMe(X)
{
  cout<<"here in printMe<float>"<< endl;
}

template <typename T,
          int value> template <typename char>
void Test<T, value>::printMe(char)
{
  cout<<"here in printMe<char>"<<endl;
}



