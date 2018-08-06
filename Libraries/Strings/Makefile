CC=g++
CFLAGS=-Wall -Wextra -pedantic
LIBNAME=libstrings.dll
INSTALLDIR=C:\tools\utils

all: $(LIBNAME)

Strings.o: Strings.cpp Strings.hpp
	$(CC) $(CFLAGS) -fPIC $^ -c

$(LIBNAME): Strings.o
	$(CC) -shared $^ -o $@

clean:
	del -y $(LIBNAME) *.o *.gch

install:
	copy /y Strings.hpp $(INSTALLDIR)
	copy /y $(LIBNAME) $(INSTALLDIR)
