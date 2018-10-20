CC=g++
INSTALLDIR=C:\tools\utils
CFLAGS=-std=gnu++14 -Wall -Wextra -pedantic -I$(INSTALLDIR) -L$(INSTALLDIR)
LIBS=
LIBNAME=libstrings.dll

all: $(LIBNAME)

Strings.o: Strings.cpp Strings.hpp
	$(CC) $(CFLAGS) -fPIC $^ -c

$(LIBNAME): Strings.o 
	$(CC) $(CFLAGS) -shared $(LIBS) $^ -o $@

clean:
	del $(LIBNAME) *.o *.gch

install:
	copy /y $(LIBNAME) $(INSTALLDIR)
	copy /y Strings.hpp $(INSTALLDIR)
