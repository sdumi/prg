#include <iostream>
#include <list>

#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
using namespace std;

#define STDIN 0

class Big
{
private:
  int _40K[10*1024];

public:
  Big(int i)
    {
      _40K[i%10000] = i;
    }
  ~Big()
    {}
};


int main(void)
{
  list<Big> bigList;

  int i = 0;
  while (i++ < 52409)
  {
    Big b(i);
    bigList.push_back(b);
  }

  while (!bigList.empty())
  {
    cout << i-- << endl;
    bigList.pop_front();
  }
  {
    struct timeval tv;
    tv.tv_sec  = 10;
    tv.tv_usec = 0; // 0.001 sec

    select(0, 0, 0, 0, &tv);
  }
  return 0;
}
