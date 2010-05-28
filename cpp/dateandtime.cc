#include <iostream>
using namespace std;


int main(void)
{

  long sec  = 123456;
  long usec = 111;
  int freq  = 100;
  int delta = 1;
  int sign  = -1;

  long MICRO_VALUE = 1000*1000;
  sec  += (sign * (delta  / freq));
  usec += ((sign * ((delta % freq) * 1000 * 1000)) / freq);
  cout << endl << "sec  = " << sec;
  cout << endl << "usec = " << usec;

  cout << endl << "after normalization:" << endl;

  cout << "sec  = " << sec << endl << "usec = " << usec << endl;
  if (sec > 0 && usec < 0)
  {
    cout << " here in if: sec = " << sec << " usec = " << usec << endl;

    sec--;
    usec+= MICRO_VALUE;
  }
  cout << "sec  = " << sec << endl << "usec = " << usec << endl;

return 0;
}
