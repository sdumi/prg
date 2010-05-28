#include "pool_allocator.h"
#include "ss_allocator.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include "timer.h"
#include <string>
#include <ctime>
#include "blockallocator.h"
#include "dum_allocator.h"
using namespace std;


const int size = 1000;
//const int size = 1024*100*3;

// struct foo
// {
//   foo(const string &s = "Hello world", int __i__ = 0):s_(s){
//     static int i = 0;
//     i_ = ++i;
//   }
//   string s_;
//   int i_;
//   bool operator <(const foo& other)const{return i_<other.i_;}
// };

struct foo
{
  int _40K[10*1024];
  int i_;
  foo(int i=0)
    {
      _40K[i%10000] = i;
      i_ = i;
//      std::cout << "size: " << sizeof (_40K) << std::endl;

    }
  ~foo()
    {}
  bool operator <(const foo& other)const{return i_<other.i_;}
};

foo generator()
{
  //  return foo("Hello world", rand());
  static int i = 0;
  foo tmp(++i);
  return tmp;
}



int main()
{
  timer t;
  srand(time(0));
  cout.precision(10);
  cout << "sizeof(size_t): " << sizeof(size_t) << endl;

  //------------------------------------------------------------
  cout<<"***Tests with <vector>***"<<endl;
  t.elapsed();
  // //  vector<foo, pool_allocator<foo> > pool_vector(size);
  // vector<foo, pool_allocator<foo> > pool_vector;
  // cout<<"Construction (pool_allocator):"<<t.elapsed()<<endl;

  // vector<foo, ss_allocator<foo> > ss_vector(size);
  // cout<<"Construction (ss_allocator):"<<t.elapsed()<<endl;

  // vector<foo> default_vector(size);
  // cout<<"Construction (default allocator):"<<t.elapsed()<<endl;

  // generate(pool_vector.begin(), pool_vector.end(), generator);

  // copy(pool_vector.begin(), pool_vector.end(), default_vector.begin());
  // copy(pool_vector.begin(), pool_vector.end(), ss_vector.begin());

  // t.elapsed();

  // sort(pool_vector.begin(), pool_vector.end());
  // cout<<"Sort (pool_allocator):"<<t.elapsed()<<endl;

  // sort(ss_vector.begin(), ss_vector.end());
  // cout<<"Sort (ss_allocator):"<<t.elapsed()<<endl;

  // sort(default_vector.begin(), default_vector.end());
  // cout<<"Sort (default allocator):"<<t.elapsed()<<endl;


  //------------------------------------------------------------
  // cout<<"***Tests with <list>***"<<endl;
  // t.elapsed();
  // list<foo, pool_allocator<foo> > pool_list(size);
  // cout<<"Construction (pool_allocator):"<<t.elapsed()<<endl;

  // list<foo, ss_allocator<foo> > ss_list(size);
  // cout<<"Construction (ss_allocator):"<<t.elapsed()<<endl;

  // list<foo> default_list(size);
  // cout<<"Construction (default allocator):"<<t.elapsed()<<endl;

  // generate(pool_list.begin(), pool_list.end(), generator);

  // copy(pool_list.begin(), pool_list.end(), default_list.begin());
  // copy(pool_list.begin(), pool_list.end(), ss_list.begin());

  // t.elapsed();

  // pool_list.sort();
  // cout<<"Sort (pool_allocator):"<<t.elapsed()<<endl;

  // ss_list.sort();
  // cout<<"Sort (ss_allocator):"<<t.elapsed()<<endl;

  // default_list.sort();
  cout<<"Sort (default allocator):"<<t.elapsed()<<endl;


  {
    cout<<"dum_allocator begin:"<<t.elapsed()<<endl;
    list<foo> ss_list2;
    list<foo, dum_allocator<foo> > ss_list0;
    list<foo, ss_allocator<foo> > ss_list1;
    // list<foo, pool_allocator<foo> > ss_list2;

     for (int i = 0; i < 1024*30; ++i)
       {
      ss_list2.push_back(generator());
       }
    cout<<"dum_allocator end: "<<t.elapsed()<<endl;
    //    sleep (1);
  }

  // {
  //   //    list<foo, ss_allocator<foo> > ss_list2;
  //   list<foo, block_allocator<foo, 1024*1024> > block_list;

  //   for (int i = 0; i < 1024; ++i)
  //     {
  //  cout << i << " ";
  //  foo tmp = generator();
  //  block_list.push_back(tmp);
  //     }
  //   cout<<"block_list2:"<<t.elapsed()<<endl;
  //   //    sleep (1);
  // }

  cout<<"Press <Enter>..."<<endl;
  char c;
  cin.getline(&c, 1);
  return 0;
}


