#ifndef DUM_ALLOCATOR_H_INCLUDED_GF
#define DUM_ALLOCATOR_H_INCLUDED_GF

#include "dum_storage.h"

template <typename T> class dum_allocator;
template <> class dum_allocator<void>
{
public:
  typedef void* pointer;
  typedef const void* const_pointer;
  // reference to void members are impossible.
  typedef void value_type;
  template <class U>
  struct rebind { typedef dum_allocator<U> other; };
};

namespace dum_alloc
{
  inline void destruct(char *){}
  inline void destruct(wchar_t*){}
  template <typename T>
  inline void destruct(T *t){t->~T();}
} // namespace dum_alloc

template <typename T>
class dum_allocator
{
public:
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;
  typedef T* pointer;
  typedef const T* const_pointer;
  typedef T& reference;
  typedef const T& const_reference;
  typedef T value_type;

  template <class U>
  struct rebind { typedef dum_allocator<U> other; };

  dum_allocator(){}
  pointer address(reference x) const {return &x;}
  const_pointer address(const_reference x) const {return &x;}
  pointer allocate(size_type size, dum_allocator<void>::const_pointer hint = 0) const
    {
      if(size == 1)
      {
        pointer p = mem_.allocate();
        if(!p)
        {
          cerr << "Could not allocate memory..." << (unsigned int )p << endl;
        }

        return p;
      }

      cerr << "this should not happen" << endl;
//      pointer p = static_cast<pointer>(mem_.allocate(size*sizeof(T)));
//      return p;
      return 0;
    }

  template <class U> dum_allocator(const dum_allocator<U>&){}
  dum_allocator(const dum_allocator<T>&){}
  void deallocate(pointer p, size_type n) const
    {
      mem_.deallocate(p, n);
    }
  void deallocate(void *p, size_type n) const
    {
      mem_.deallocate(p, n);
    }
  size_type max_size() const throw() {return size_t(-1) / sizeof(value_type);}
  void construct(pointer p, const T& val)
    {
//      cerr << (unsigned int)p << "  ";
      if ((unsigned int) p > 0x100)
      {
        new(static_cast<void*>(p)) T(val);
      }
      else
      {
        cerr<<"try to construct a null pointer" << endl;
      }
    }
  void construct(pointer p)
    {
//      cerr << (unsigned int)p << " ";

      if ((unsigned int)p > 0x100)
      {
        new(static_cast<void*>(p)) T();
      }
      else
      {
        cerr<<"try to construct a null pointer" << endl;
      }
    }
  void destroy(pointer p)
    {
      dum_alloc::destruct(p);
    }
  static void dump()
    {
      mem_.dump();
    }
private:

  static dum_storage<T> mem_;
};

template <typename T> dum_storage<T> dum_allocator<T>::mem_;

template <typename T, typename U>
inline bool operator==(const dum_allocator<T>&, const dum_allocator<U>){return true;}

template <typename T, typename U>
inline bool operator!=(const dum_allocator<T>&, const dum_allocator<U>){return false;}


#endif


