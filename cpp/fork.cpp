//#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
using namespace std;
int main()
{
  pid_t child_pid;
  
  cout << "the main program process ID is: " << (int) getpid() << endl;

  child_pid = fork();
  if (child_pid != 0)
    {
      cout << "this is the parent process, with id: " << (int) getpid() << endl;
      cout << "the child's process ID is: " << (int) child_pid << endl;
    }
  else
    {
      cout << "this is the child process, with id: " << (int) getpid() << endl;
    }
  return 0;
}
