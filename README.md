#  projects
Created a generic Makefile for both c and cpp files.
source structure

|Directory|Type|Last Updated|
|---|---|---|
|src_c | c files|
|src_cpp | c++ files|
|obj | obj files  |
|bin | executable |
|include_c | C include files |
|include_cpp | C++ include files |

# For compiling 'c' code
- make all CC=gcc
- make all CC=gcc CFLAGS+="-g" LFLAGS+="-lcrypto" -> for md5sum
# For compiling 'c++' code
> make all
# To cleanup everything
> make destroy 
# For passing CFLAGS or LFLAGS(linking)
> make all CC=gcc CFLAGS+=-DDEBUG
# For using valgrind
- make all CFLAGS+="-g" LFLAGS+="-g"
- valgrind -v --tool=memcheck --leak-check=yes --leak-check=full --show-leak-kinds=all 
- valgrind -v --tool=memcheck --leak-check=yes bin/cppproject
# Mac
> make all CC=gcc CFLAGS+="-I/Users/pgopan/anaconda/pkgs/openssl-1.0.2j-0/include"
# To kill application
> kill -9 $(ps -eaf | grep -i "cproject" | grep -v grep | awk '{print $2}')
# For building kernel module
> make clean;make all;
# objdump
> objdump -Swx --line-numbers <object>
# Use following to debug malloc/free of a process
> gdb -x gdbs_free -p <pid>
