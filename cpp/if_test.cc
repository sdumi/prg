#include <iostream>
using namespace std;


int main(void)
{

  typedef bool DDBoolean;

  // simulate a not initialized DDBoolean
  // memory under DDBoolean > 1
  char b[1];
  b[0] = 7;   // something > 1
  DDBoolean* b2 = new(b) DDBoolean;
  unsigned int bc2 = *b2;
  cout << bc2 << endl;
  if ( *b2  > 1 )            //       <<<<< warning: comparison is always false due to limited range of data type
    cout << "*b2  > 1" << endl;
  else
    cout << " NOT   *b2  > 1" << endl;
  return 0;




  typedef bool DDBoolean;

  bool src_b = 7;

  unsigned int src = src_b;

  cout << src << endl;


  if (src > 1)
    cout << "TRUE" << endl;
  else
    cout << "FALSE" << endl;

  return 0;
}
