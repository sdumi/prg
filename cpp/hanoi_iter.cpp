#include <iostream>
#include <stack>
#include <stdlib.h>
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
  cout << endl << "--------------------" << endl;
  hanoi(nr, 'a', 'b', 'c');
  cout  << "--------------------" << endl;
  return 0;
}

typedef enum
{
  e_Invalid = 0,
  e_d__s = 1, //dst    to src
  e_d__i = 2, //dst    to interm
  e_s__d = 3, //src    to dst
  e_s__i = 4, //src    to interm
  e_i__d = 5, //interm to dst
  e_i__s = 6  //interm to src
} E_Moves;

typedef std::stack<int> Stack;

E_Moves makeNewMove(int n, Stack& src, Stack& dst, Stack& interm, E_Moves prevMove);

void hanoi(int n, char src, char dst, char interm)
{
////  cout << "n == " << n << endl;

  if (n <= 0)
    return;
  Stack _src, _dst, _interm;
  //initialize our three stacks:
  //
  // src          interm           dst
  //  1
  //  2
  // ...
  //  n
  // n+1           n+2             n+3
  //
  {
    _dst.push(n+3);
    _interm.push(n+2);
    int i = n+1;
    while (i!=0)
      _src.push(i--);
  }
  {
////    cout << " src.size()   == " << _src.size()    << endl;
////    cout << " dst.size()   == " << _dst.size()    << endl;
////    cout << " inter.size() == " << _interm.size() << endl;
  }
  // our main loop:
  // stop condition:
  //     n discs are moved to _dst
  // rules:
  //     a disc can be moved only to a stack where the top disc has a higher number
  //     cannot move a disc on top of a disc with the same parity (odd, even)
  //     cannot repeat the previous state (move).
  //
  {
    E_Moves currentMove = e_i__d; //doesn't really matter actually as long as the move is not something e_s__*

    while (_dst.size() != n+1) //stop condition
    {
      // Yupeee!
      // find the "from --> to" move :)
      currentMove = makeNewMove(n, _src, _dst, _interm, currentMove);
//      cout << "currentMove = " << currentMove;
      if (currentMove == e_Invalid)
      {
        cerr << endl <<"Some invalid move found...." << endl;
        return;
      }
      // our move is a valid one;
      //print something on the screen
      {
        char __dst, __src;

        switch (currentMove)
        {
          case e_d__i:
            __src = dst;
            __dst = interm;
            break;
          case e_d__s:
            __src = dst;
            __dst = src;
            break;
          case e_s__i:
            __src = src;
            __dst = interm;
            break;
          case e_s__d:
            __src = src;
            __dst = dst;
            break;
          case e_i__s:
            __src = interm;
            __dst = src;
            break;
          case e_i__d:
            __src = interm;
            __dst = dst;
            break;
          default:
            cerr << endl << "invalid currentMove found: " << currentMove << endl;
            return;
        }
        cout << __src << " --> " << __dst << endl;
      }
    }
  }
  return;
}

void print_usage(int argc, char **argv)
{
  cout << endl;
  cout << "Usage: " << argv[0] << " number_of_discs" << endl;
}

  // rules:
  //     a disc can be moved only to a stack where the top disc has a higher number
  //     cannot move a disc on top of a disc with the same parity (odd, even)
  //     cannot repeat the previous state (move).
E_Moves makeNewMove(int n, Stack& src, Stack& dst, Stack& interm, E_Moves prevMove)
{
  E_Moves move = e_Invalid;

  //try to move something from src:
  if (src.top() <= n)
  {
    //try s --> d
    if ((src.top() < dst.top()) &&              // has to be lower
        ((src.top() % 2) != (dst.top() % 2)) && // must have different parity
        (prevMove != e_d__s))                   // this move should not revert us to previous state
    {
      dst.push(src.top());
      src.pop();
      move = e_s__d;
      return move;
    }
    //try s --> i
    if ((src.top() < interm.top()) &&              // has to be lower
        ((src.top() % 2) != (interm.top() % 2)) && // must have different parity
        (prevMove != e_i__s))                   // this move should not revert us to previous state
    {
      interm.push(src.top());
      src.pop();
      move = e_s__i;
      return move;
    }
  }

  //try to move something from dst:
  if (dst.top() <= n)
  {
    //try d --> s
    if ((dst.top() < src.top()) &&              // has to be lower
        ((dst.top() % 2) != (src.top() % 2)) && // must have different parity
        (prevMove != e_s__d))                   // this move should not revert us to previous state
    {
      src.push(dst.top());
      dst.pop();
      move = e_d__s;
      return move;
    }
    //try d --> i
    if ((dst.top() < interm.top()) &&              // has to be lower
        ((dst.top() % 2) != (interm.top() % 2)) && // must have different parity
        (prevMove != e_i__d))                   // this move should not revert us to previous state
    {
      interm.push(dst.top());
      dst.pop();
      move = e_d__i;
      return move;
    }
  }

  //try to move something from interm:
  if (interm.top() <= n)
  {
    //try i --> s
    if ((interm.top() < src.top()) &&              // has to be lower
        ((interm.top() % 2) != (src.top() % 2)) && // must have different parity
        (prevMove != e_s__i))                   // this move should not revert us to previous state
    {
      src.push(interm.top());
      interm.pop();
      move = e_i__s;
      return move;
    }
    //try i --> d
    if ((interm.top() < dst.top()) &&              // has to be lower
        ((interm.top() % 2) != (dst.top() % 2)) && // must have different parity
        (prevMove != e_d__i))                   // this move should not revert us to previous state
    {
      dst.push(interm.top());
      interm.pop();
      move = e_i__d;
      return move;
    }
  }

  return move;
}
