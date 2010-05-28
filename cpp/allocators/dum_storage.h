#ifndef DUM_STORAGE_H_INCLUDED_GF
#define DUM_STORAGE_H_INCLUDED_GF

#include <new>
#include <list>
#include <set>
#include <algorithm>
#include <iostream> //for dump()
using namespace std;

template <typename T>
class dum_storage
{
  // we initially have a capacity of init_size elements:
  enum dum_defaults{init_size = 1024};
public:
  dum_storage();
  T* allocate();
  void* allocate(size_t n);
  void deallocate(void *p, size_t n);
  void dump();
  ~dum_storage();

private:
  // deprecated:
  struct link
  {
    link *next_;
  };

  // all chunks of memory will start with one block containing one element of the
  // following struct:
  struct hdr
  {
    set<char*> free_blocks;
    set<char*> allocd_blocks;
  };

  void grow();
  void shrink();

  bool verify_memory_contiguous(link *l, int n);

  // this struct deallocates the chunk of memory pointed by *p
  struct killer
  {
    void operator()(char *p){delete [] p;}
  };

  size_t size_;
  size_t step_;

  // this list stores pointers to our chunks of allocated memory
  std::list<char *> dum_mem_;

  link *head_;

  char* addNewChunk();
  void initChunk(char *p);
  hdr* getHdr(char *p);
};

#include "dum_storage.hcc"
#endif
