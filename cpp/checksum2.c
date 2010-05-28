#include <stdio.h>

int main(int argc, char *argv[])
{
  FILE *CheckFile;
  int Byte;
  unsigned int Checksum;

  if (argc != 2)
  {
    printf("Usage: checksum2 filename\n");
    exit(1);
  }

  if ((CheckFile = fopen(argv[1], "rb")) == NULL)
  {
    printf("Can't open file: %s\n", argv[1]);
    exit(1);
  }

  /*Initialize the checksum accumulator*/
  Checksum = 0;

  /*Add each byte in turn into the checksum accumulator*/
  while ((Byte = getc(CheckFile)) != EOF)
  {
    Checksum += (unsigned int) Byte;
  }

  /*Report the result*/
  printf("The result is: %u\n", Checksum);
  exit(0);
}
