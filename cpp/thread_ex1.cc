#include <pthread.h>
#include <iostream>
using namespace std;

int i = 0;
void* print_xs(void* unused);
int main(void)
{
  pthread_t thread_id;
  pthread_create(&thread_id, NULL, &print_xs, NULL);
  while (i<500)
  {
    ++i;
    cerr << 'o' << i << " ";
  }
  return 0;
}

void* print_xs(void*)
{
  while (i<250)
  {
    ++i;
    cerr << 'x' << i <<" ";
  }
}


