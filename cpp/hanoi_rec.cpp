#include <iostream>
using namespace std;

void print_usage(int argc, char **argv);
void hanoi(int n, char src, char dst, char interm);

int main(int argc, char** argv)
{
  if (argc != 2)
  {
    print_usage(argc, argv);
    exit(1);
  }

  int nr = atoi(argv[1]);
  cout << endl << "--------------------";
  hanoi(nr, 'a', 'b', 'c');
  cout << endl << "--------------------" << endl;
  return 0;
}

void hanoi(int n, char src, char dst, char interm)
{
  if (n <= 0)
    return;
  //move n-1 discs from src to interm
  hanoi(n-1, src, interm, dst);
  //move 1 disc (last one) from src to dst
  cout << endl << src << " --> " << dst;
  //move n-1 discs from interm to dst
  hanoi(n-1, interm, dst, src);
}

void print_usage(int argc, char **argv)
{
  cout << endl;
  cout << "Usage: " << argv[0] << " number_of_discs." << endl;
}
