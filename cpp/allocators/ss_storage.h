#ifndef SS_STORAGE_H_INCLUDED_GF
#define SS_STORAGE_H_INCLUDED_GF

#include <new>
#include <list>
#include <algorithm>
#include <iostream> //for dump()

template <typename T>
class ss_storage
{
  enum ss_defaults{init_size = 1024};
public:
  ss_storage();
  T* allocate();
  void* allocate(size_t n);
  void deallocate(void *p, size_t n);
  void dump();
  ~ss_storage();

private:
  struct link
  {
    link *next_;
  };

  void grow();
  bool verify_memory_contiguous(link *l, int n);

  struct killer
  {
    void operator()(char *p){delete [] p;}
  };

  size_t size_;
  size_t step_;
  std::list<char *> ss_mem_;
  link *head_;

};

#include "ss_storage.cpp"
#endif
