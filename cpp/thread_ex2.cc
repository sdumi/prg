#include <pthread.h>
#include <iostream>
using namespace std;


struct char_print_params
{
  char character;
  int count;
};

void* char_print(void* parameters)
{

  cout << "enter thread...:" << endl;
  struct char_print_params* p = (struct char_print_params*) parameters;

  for(int i=0; i<p->count; ++i)
  {
    cerr<<p->character;
  }
  cout << "exit from thread...:" << endl;
  return NULL;
}

int main(void)
{
  pthread_t thread1_id, thread2_id;
  struct char_print_params thread1_args, thread2_args;
  thread1_args.character = 'x';
  thread1_args.count = 300;

  thread2_args.character = 'o';
  thread2_args.count = 200;

  cout << "starting first thread:" << endl;

  pthread_create(&thread1_id, NULL, &char_print, &thread1_args);
  cout << "starting second thread:" << endl;
  pthread_create(&thread2_id, NULL, &char_print, &thread2_args);

  pthread_join(thread1_id, NULL);
  pthread_join(thread2_id, NULL);


  cout << "exit from main...:" << endl;
  return 0;
}


