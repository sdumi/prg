#include <iostream>
#include <set>
using namespace std;

struct hdr
{
  set<char*> free_blocks;
  set<char*> allocd_blocks;
};


int main(void)
{
  cout << "Hello world!" << endl;

  set <char*> tst;
  cout << "sizeof(tst): " << sizeof (tst) << endl;
  cout << "tst.size(): " << tst.size() << endl;

  char *p = "Hi mate!";
  tst.insert(p);
  cout << "sizeof(tst): " << sizeof (tst) << endl;
  cout << "tst.size(): " << tst.size() << endl;

  char *c = "Hi there!";
  tst.insert(c);
  cout << "sizeof(tst): " << sizeof (tst) << endl;
  cout << "tst.size(): " << tst.size() << endl;

  cout << "sizeof(hdr): " << sizeof(hdr) << endl;

  return 0;
}
