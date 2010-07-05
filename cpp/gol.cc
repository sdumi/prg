#include <iostream>
using namespace std;

const int WIDTH  = 10;
const int HEIGHT = 10;


void setPattern(int p[][HEIGHT]);


int main(void)
{
  int origTable[WIDTH][HEIGHT];
  int tmpTable[WIDTH][HEIGHT];

  int k = 5;

  setPattern(origTable);
  while (k--)
  {
//    cout << "------" << endl;

    for (int i = 0; i < WIDTH; ++i)
    {
      for (int j = 0; j < HEIGHT; ++j)
      {
        int NW = ((i > 0) && (j > 0))? origTable[i-1][j-1] : 0;
        int N  = (i > 0) ? origTable[i-1][j] : 0;
        int NE = ((i > 0) && ((j+1) < HEIGHT)) ? origTable[i-1][j+1] : 0;
        int W  = (j > 0) ? origTable[i][j-1] : 0;
        int E  = ((j + 1) < HEIGHT) ? origTable[i][j+1] : 0;
        int SW = (((i+1) < WIDTH) && (j > 0)) ? origTable[i+1][j-1] : 0;
        int S  = (((i+1) < WIDTH)) ? origTable[i+1][j] : 0;
        int SE = (((i+1) < WIDTH) && ((j+1) < HEIGHT)) ? origTable[i+1][j+1] : 0;


        tmpTable[i][j] =  NW + N + NE + W + E + SW + S + SE;
//        cout << "i = " << i << ", j = " << j << ", [][] =" << tmpTable[i][j];

      }
    }
    for (int i = 0; i < WIDTH; ++i)
    {
      for (int j = 0; j < HEIGHT; ++j)
      {
        if ((tmpTable[i][j] != 2) && (tmpTable[i][j] != 3))
          origTable[i][j] = 0;
        if (tmpTable[i][j] == 3)
          origTable[i][j] = 1;

        cout << origTable[i][j] << " ";
      }
      cout <<endl;
    }
    cout << endl;
  }




  return 0;
}

void setPattern(int p[][HEIGHT])
{
  for (int i = 0; i < WIDTH; ++i)
    for (int j = 0; j < HEIGHT; ++j)
      p[i][j] = 0;


  p[4][3] = 1;
  p[4][4] = 1;
  p[5][3] = 1;
}
