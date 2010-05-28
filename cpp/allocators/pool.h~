#ifndef POOL_H_INCLUDED_GF
#define POOL_H_INCLUDED_GF
#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable:4018) //signed/unsigned mismatch
#pragma warning(disable:4290) // exception spec ignored
#endif

#include <exception>
#include <list>
#include <algorithm>
#include <iostream>  //for dump()

class pool
{
    class logic_error:public std::exception
    {
    public:
        logic_error(const char *what):what_(what){}
            const char* what(){return what_;}
    private:
        const char *what_;
    };
    enum pool_defaults{
        init_size = 0xfffff,
        min_size = 0xf
    };
public:
    pool(size_t size = init_size):size_(size)
    {
        if(size_-sizeof(block) < min_size) throw logic_error("Initial pool size too small");
        pool_mem_.push_back(new char[size_]);
        blocks_ = reinterpret_cast<block*>(*(pool_mem_.begin()));
        blocks_->prev_= 0;
        blocks_->next_= 0;
        blocks_->free_= 1;
        blocks_->size_= size_-sizeof(block);
    };
    ~pool()
    {
        std::for_each(pool_mem_.begin(), pool_mem_.end(), killer());
    }

    void* allocate(size_t size)
    {
        if(size>size_- sizeof(block)) throw std::bad_alloc();
        block *b = blocks_;
        while(1){
            while(!b->free_){
                if(!b->next_) grow(b);
                b=b->next_;
            }
            if(b->size_<size) continue;
            break;
        }
        if(b->size_ - size < 2*sizeof(block)){
            b->free_=0;            
            return reinterpret_cast<char *>(b) + sizeof(block);
        }
        else{
            block * new_block = (reinterpret_cast<block *>(reinterpret_cast<char *>(b) 
                + size + sizeof(block)));
            if(b->next_) b->next_->prev_ = new_block;
            new_block->next_ = b->next_;
            b->next_ = new_block;
            new_block->prev_ = b;
            b->free_ = 0;
            new_block->size_= b->size_ - size - sizeof(block);
            b->size_ = size;
            new_block->free_ = 1;
            return reinterpret_cast<char *>(b) + sizeof(block);
        }
            
    }

    void deallocate(void *p, size_t = 0)
    {
        if(!p) return;
        block *b = reinterpret_cast<block *>(static_cast<char*>(p) - sizeof(block));
        if(b->prev_ && b->next_){
            if(b->prev_->free_ && b->next_->free_){
                b->prev_->size_ += b->size_ + b->next_->size_ + 2*sizeof(block);
                b->prev_->next_ = b->next_->next_;
                if(b->next_->next_)b->next_->next_->prev_ = b->prev_;
                return;
            }
        }
        if(b->prev_){
            if(b->prev_->free_){
                b->prev_->size_ += b->size_ + sizeof(block);
                b->prev_->next_=b->next_;
                if(b->next_) b->next_->prev_ = b->prev_;
                b->free_= 1;
                return;
            }
        }
        if(b->next_){
            if(b->next_->free_){
                b->size_ += b->next_->size_ + sizeof(block);
                b->next_ = b->next_->next_;
                if(b->next_) b->next_->prev_ = b;
                b->free_= 1;
                return;
            }
        }
        b->free_ = 1;
    }
    void dump()
    {
        using namespace std;
        block *b = blocks_;
        while(1){
            cout<<"Size="<<b->size_<<", free="<<b->free_<<
                ", prev="<<b->prev_<<", next="<<b->next_<<endl;
            if(b->next_) b = b->next_;
            else break;
        }
    }
private:
    size_t size_;
    std::list<char *> pool_mem_;
    struct block{
        block *prev_;
        block *next_;
        size_t size_;
        int free_;
        block(block *prev, block *next, size_t size, int free): 
        prev_(prev), next_(next), size_(size), free_(free){}
        ~block(){}
    };
    block * blocks_;
    pool(const pool &);
    pool& operator=(const pool&);
    struct killer
    {
        void operator()(char *p){delete [] p;}
    };
    static void kill(char *p){delete [] p;}
    void grow(block *b)
    {
        block *new_block;
        char *p = new char[size_];
        pool_mem_.push_back(p);
        new_block = reinterpret_cast<block*>(p);
        new_block->prev_= b;
        new_block->next_= 0;
        new_block->free_= 1;
        new_block->size_= size_-sizeof(block);
        b->next_ = new_block;
    }
};

#ifdef _WIN32
#pragma warning(pop)
#endif

#endif

