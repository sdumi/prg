CC=g++
CFLAGS=-c -Wall
#SOURCES=main.cpp hello.cpp factorial.cpp
#OBJECTS=$(SOURCES:.cpp=.o)
#EXECUTABLE=hello


all: stl_memory_test

stl_memory_test: stl_memory_test.o 
	$(CC) stl_memory_test.o -o stl_memory_test 

stl_memory_test.o: stl_memory_test.cpp ss_storage.h ss_allocator.h ss_storage.cpp
	$(CC) $(CFLAGS) -c stl_memory_test.cpp

clean:
	rm -rf *.o stl_memory_test core.* alloc	

alloc: main.cpp timer.cpp timer.h ss_storage.h ss_storage.cpp ss_allocator.h pool_allocator.h pool.h dum_storage.h dum_storage.hcc dum_allocator.h
	$(CC) -o alloc main.cpp timer.cpp