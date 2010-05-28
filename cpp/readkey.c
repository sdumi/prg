#include <iostream>
#include <stdio.h>
#include <termio.h>
#include <curses.h>

#define VK    27
#define VK2   91
#define UP    65
#define DOWN  66
#define RIGHT 67
#define LEFT  68

using namespace std;

void set_keypress(void) {
  struct termios new_settings, stored_settings;
  // Get the current settings
  tcgetattr(0,&stored_settings);
  new_settings = stored_settings;

  // Remove printing of special characters
  new_settings.c_lflag &= (~ICANON);

  // Remove wait time
  new_settings.c_cc[VTIME] = 0;
  tcgetattr(0,&stored_settings);
  new_settings.c_cc[VMIN] = 1;
  tcsetattr(0,TCSANOW,&new_settings);
}

int main()
{
  set_keypress();

  int key;
  while(true)
  {
    key = getchar();
    cout << "key = " << key << endl;
    if(key == VK)
    {
      if(getchar() == VK2)
      {
        switch(getchar())
        {
        case UP:
          cout << "key = UP ARROW" << endl;
          break;
        case DOWN:
          cout << "key = DOWN ARROW" << endl;
          break;
        case LEFT:
          cout << "key = LEFT ARROW" << endl;
          break;
        case RIGHT:
          cout << "key = RIGHT ARROW" << endl;
          break;
        }
      }
    }
  }

  return 0;
}
