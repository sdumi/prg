#include "ss_storage.h"
//#define DEBUG on
//------------------------------------------------------------
//
template <class T> ss_storage<T>::ss_storage():
  size_(sizeof(link) > sizeof(T) ? init_size * sizeof(link) : init_size*sizeof(T)),
  step_(sizeof(link) > sizeof(T) ? sizeof(link) : sizeof(T))
{
  #ifdef DEBUG
  std::cout << "ss_storage::ss_storage()" << std::endl;
  #endif
  std::cout << "size_: " << size_ << std::endl;
  ss_mem_.push_back(new char[size_]);
  link *l;
  head_ = l = reinterpret_cast<link *>(*ss_mem_.begin());
  for(int i = 1; i<init_size; ++i)
  {
    l->next_ = reinterpret_cast<link *>(*ss_mem_.begin() + i*step_);
    l = l->next_;
  }
  l->next_ = 0;
}

//------------------------------------------------------------
//
template <class T>
T* ss_storage<T>::allocate()
{
  #ifdef DEBUG
  std::cout << "ss_storage::allocate()" << std::endl;
  std::cout << "head_ == " << head_ << std::endl;
  #endif
  // no more room available
  // allocate a new segment:
  while (!head_)
    {
      grow();
    }

  link *l = head_;


  head_ = head_->next_;
  #ifdef DEBUG
  std::cout << "l == " << l << std::endl;
  std::cout << "head_ == " << head_ << std::endl;
  #endif

  T* p = reinterpret_cast<T *>(l);

  #ifdef DEBUG
  std::cout << "p == " << p << std::endl;
  #endif

  return p;
}

//------------------------------------------------------------
//
template<class T>
void* ss_storage<T>::allocate(size_t n)
{
  //  #ifdef DEBUG
  std::cout << "ss_storage::allocate(size_t): " << n << std::endl;
  //  #endif

  link *l = head_, *conn, *ret;
  if(n%step_) n = step_*(n/step_+1);
  while(1)
  {
    if(verify_memory_contiguous(l->next_, n/step_))
    {
      //      #ifdef DEBUG
      std::cout <<"!";
      //      #endif

      conn = ret = l->next_;
      for (unsigned int i=0; i<n/step_; ++i)
      {
        conn = conn->next_;
      }

      l->next_ = conn;
      return ret;
    }
    if ( l->next_ )
    {
      //      #ifdef DEBUG
      //      std::cout <<"@";
      //      #endif
      l = l->next_;
    }
    else
    {
      #ifdef DEBUG
      std::cout <<"#";
      #endif

      grow();
      l = head_;
    }
  }
}

//------------------------------------------------------------
//
template<class T>
void ss_storage<T>::deallocate(void *p, size_t n)
{
  #ifdef DEBUG
  std::cout <<"deallocate()";
  #endif

  if(n<=step_)
  {
    link *l = head_;
    head_ = reinterpret_cast<link*>(p);
    head_->next_=l;
  }
  else
  {
    link *l = head_, *conn;
    head_ = reinterpret_cast<link*>(p);
    conn = head_;
    for(unsigned int i=0; i<n/step_; ++i)
    {
      conn->next_ = reinterpret_cast<link*>(p) + i;
      conn = conn->next_;
    }
    conn->next_ = l;
  }
}

//------------------------------------------------------------
//
template<class T>
void ss_storage<T>::dump()
{
  using namespace std;
  link *l = head_;
  int links = 0;
  size_t free_space = 0;
  while(l->next_){
    free_space += step_;
    ++links;
    l = l->next_;
  }
  cout<<"Free space: "<<links*step_<<", links: "<<links<<endl;
}

//------------------------------------------------------------
//
template<class T>
ss_storage<T>::~ss_storage()
{
  std::for_each(ss_mem_.begin(), ss_mem_.end(), killer());
}

//------------------------------------------------------------
//
template<class T>
void ss_storage<T>::grow()
{
  #ifdef DEBUG
  std::cout << "grow() " << std::endl;
  std::cout << "head_: " << head_ << std::endl;
  #endif

  char *new_chunk = new char[size_];

  ss_mem_.push_back(new_chunk);

  link *old_head = head_;
  #ifdef DEBUG
  std::cout << "old_head: " << old_head << std::endl;
  #endif

  link *l = reinterpret_cast<link *>(new_chunk);
  #ifdef DEBUG
  std::cout << "l: " << l << std::endl;
  #endif

  head_ = l;
  #ifdef DEBUG
  std::cout << "head_: " << head_ << std::endl;
  #endif

  for(int i = 1; i<init_size; ++i){
    l->next_ = reinterpret_cast<link *>(new_chunk + i*step_);
    l = l->next_;
  }

  #ifdef DEBUG
  std::cout << "l: " << l << std::endl;
  #endif
  l->next_ = old_head;
  #ifdef DEBUG
  std::cout << "l->next: " << l->next_ << std::endl;
  #endif
}

//------------------------------------------------------------
//
template<class T>
bool ss_storage<T>::verify_memory_contiguous(link *l, int n)
{
  if(!l) return false;
  for(int i=0; i<n; ++i){
    if(l->next_){
      if(reinterpret_cast<char*>(l->next_) - reinterpret_cast<char*>(l) == step_){
        l = l->next_;
      }
      else{
        return false;
      }
    }
    else{
      return false;
    }
  }
  return true;
}
