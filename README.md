# projects
Created a generic Makefile for both c and cpp files.
source structure
	src/ 	 ---> all c/c++ files
	obj/ 	 ---> all obj files
	bin/	 ---> all executable files
	include/ ---> all header files
For compiling 'c' code
    make all CC=gcc
    make all CC=gcc CFLAGS+="-g" LFLAGS+="-lcrypto" -> for md5sum
For compiling 'c++' code
    make all
To cleanup everything
make destroy 
For passing CFLAGS or LFLAGS(linking)
make all CC=gcc CFLAGS+=-DDEBUG
For using valgrind
make all CFLAGS+="-g" LFLAGS+="-g"
valgrind -v --tool=memcheck --leak-check=yes --leak-check=full --show-leak-kinds=all 
valgrind -v --tool=memcheck --leak-check=yes bin/cppproject
