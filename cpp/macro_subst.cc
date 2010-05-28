//#include <iostream>
//using namespace std;

#define INCLUDE                                 \
  #ifndef macro_subst_h                         \
  #include <iostream>                           \
  #include "macro_subst.h"                      \
  #endif

#define MACRO1(param) {                         \
    if (1==param){                              \
      cout << "1=="<< param <<endl;             \
    }                                           \
    else{                                       \
      cout << "1!=" << param <<endl;            \
    }                                           \
  }

#define MACRO2(param) {                         \
    cout << "param==" << param << endl;         \
    if (param > 5){                             \
      int n = param%5;                          \
      MACRO1(n);                                \
    }                                           \
    else{                                       \
      MACRO1(param);                            \
    }                                           \
  }

/*INCLUDE;*/
  #ifndef macro_subst_h
  #include <iostream>
  #include "macro_subst.h"
  #endif


int main(void)
{
  cout << "++ main" << endl;
  MACRO2(2);
  MACRO2(11);
  cout << "-- main" << endl;
  return 0;
}




