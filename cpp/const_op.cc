#include <iostream>
using namespace std;

class A
{
public:
  const int& operator[](const int& i) const
    {
      cout<<"second" << endl;
      return x;
    }
  int& operator[](const int& i)
    {
      cout<< "first" << endl;
      return x;
    }



  int qqq(const int& i)
    {
      cout<<"third"<<endl;
      return x;
    }
  int  qqq(const int& i) const
    {
      cout<<"fourth"<<endl;
      return x;
    }

  int x;

};

void aaa(const A& x)
{x.qqq(9);}



int main (void)
{
  A a;
//   a[0] = 1;
//   const int & x =  a[1];

  aaa(a);


//   if (1 == a[1])
//   {
//     cout <<"inside if" <<endl;
//   }

//   a.qqq(1);


  return 0;
}


