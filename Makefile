CC = g++-4.6

CFLAGS_DEBUG := -g -Wall -std=c++0x
CFLAGS_RELEASE := -Wextra -pedantic -O3 -std=c++0x

LIBINCLUDE := -I./lib/include -I./lib/boost_1_54_0 -I/usr/include/boost 

LDFLAGS := -lXxf86vm -lGLU -lX11


LBOOST := ./lib/boost_1_54_0/installed/lib/libboost_filesystem.so \
          ./lib/boost_1_54_0/installed/lib/libboost_system.so \
	  ./lib/boost_1_54_0/installed/lib/libboost_program_options.so

LIRR := lib/libIrrlicht.a

BINARY_DEBUG := bin/hmv_dbg.exe
BINARY := bin/hmv.exe


all: main.o viewer.o commandLineArgumentParser.o
	$(CC) $(CFLAGS_DEBUG) $(LIBINCLUDE) $(LDFLAGS) viewer.o commandLineArgumentParser.o main.o $(LBOOST) $(LIRR) -o $(BINARY_DEBUG)

viewer.o: 
	$(CC) $(CFLAGS_DEBUG) $(LIBINCLUDE) -c viewer/viewer.cpp -o viewer.o

main.o:
	$(CC) $(CFLAGS_DEBUG) $(LIBINCLUDE) -c main.cpp -o main.o

commandLineArgumentParser.o:
	$(CC) $(CFLAGS_DEBUG) $(LIBINCLUDE) -c args/commandLineArgumentParser.cpp -o commandLineArgumentParser.o

#release:

#test: 

clean:
	rm -f *.o