#include <stdio.h>
#include <fcntl.h>
#include <malloc.h>

#define BUFFER_SIZE 0x1000 /*32Kb data buffer*/
main(int argc, char *argv[])
{
  int Handle;
  unsigned int Checksum;
  unsigned char *WorkingBuffer, *WorkingPtr;
  int WorkingLength, LengthCount;

  if (argc != 2)
  {
    printf("usage: checksum3 filename\n");
    exit(1);
  }
  if ((Handle = open(argv[1], O_RDONLY)) == -1)
  {
    printf("Can't open file: %s\n", argv[1]);
    exit(1);
  }

  /*Get memory in which to buffer the data*/
  if ((WorkingBuffer = malloc(BUFFER_SIZE)) == NULL)
  {
    printf("Can't get enough memory\n");
    exit(1);
  }

  Checksum = 0;
  do
  {
    if ((WorkingLength = read(Handle, WorkingBuffer, BUFFER_SIZE)) == -1)
    {
      printf("Error reading file: %s\n", argv[1]);
      exit(1);
    }

    /*Checksum this chunk*/
    WorkingPtr = WorkingBuffer;
    LengthCount = WorkingLength;
    while (LengthCount--)
    {
      Checksum += (unsigned int) *WorkingPtr++;
    }
  } while (WorkingLength);

  printf("The checksum is: %u\n", Checksum);
  exit(0);
}


