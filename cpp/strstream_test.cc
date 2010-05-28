#include <iostream>
#include <sstream>
using namespace std;

int main ()
{
  cout << "hello world!" << endl;

  string result;
  stringstream str;
//   str << "Vio" << setw(4) << setfill('0') << (katag++ % 10000);
//   result = katagStr.str();
  char res[100];
  int W = 3;
  int P = 4;
  float f = 3.141562;
  sprintf(res, "%*.*f", W, P, f);
  printf("%s\n", res);
}
