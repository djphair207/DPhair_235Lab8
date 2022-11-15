TARGETS = AVLlab

CC = g++
CCFLAGS = -g -std=c++11

all:	$(TARGETS)

AVLlab:	maintest.cpp AVL.h AVL.cpp AVLInterface.h NodeInterface.h Node.h Node.cpp 
	$(CC) $(CCFLAGS)  -o AVLlab main.cpp AVL.cpp Node.cpp

.PHONY:	clean

clean:
	rm -f *.o
	rm -f $(TARGETS)
