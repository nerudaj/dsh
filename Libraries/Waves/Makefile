CC=g++
INSTALLDIR=C:\tools\utils
CFLAGS=-std=gnu++14 -Wall -Wextra -pedantic -I$(INSTALLDIR) -L$(INSTALLDIR)
LIBS=
LIBNAME=libwaves.dll

all: $(LIBNAME)

waves.o: waves.cpp waves.hpp
	$(CC) $(CFLAGS) -fPIC $^ -c

$(LIBNAME): waves.o 
	$(CC) $(CFLAGS) -shared $(LIBS) $^ -o $@

clean:
	del $(LIBNAME) *.o *.gch

install:
	copy /y $(LIBNAME) $(INSTALLDIR)
	copy /y waves.hpp $(INSTALLDIR)
