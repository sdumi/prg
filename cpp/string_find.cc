#include <iostream>
#include <string>
using namespace std;

int main(void)
{
  string str("test 1 TRC=\"incredibil dar adevarat\"vtes");

  if (str.find("TRC=\"d") != string::npos)
  {
    cout << "we found test" << endl;
  }

  cout << endl << "Hello World!" << endl;

  return 0;
}

