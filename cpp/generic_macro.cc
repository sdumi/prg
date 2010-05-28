//#include <iostream>
//using namespace std;

#define min(x, y) ({                            \
      typeof(x) _min1 = (x);                    \
      typeof(y) _min2 = (y);                    \
      (void) (&_min1 == &_min2);                \
      _min1 < _min2 ? _min1 : _min2; })


int main(void)
{
  int x = 4;
  int y = 56;

  int minim = min(x, x);

//  cout << "minimum between: (" << x << " , " << y << ") is: " << minim << endl;
  return 0;
}

