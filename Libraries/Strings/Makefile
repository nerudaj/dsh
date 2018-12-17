CC=g++
INSTALLDIR=C:\tools\utils
CFLAGS=-std=gnu++14 -Wall -Wextra -pedantic -I$(INSTALLDIR) -L$(INSTALLDIR)
LIBS=
LIBNAME=libstrings.dll

all: $(LIBNAME)

Strings.o: Strings.cpp Strings.hpp
	$(CC) $(CFLAGS) -fPIC $^ -c

$(LIBNAME): Strings.o 
	$(CC) $(CFLAGS) -shared $(LIBS) $^ -o $@ -Wl,--out-implib,libstrings.lib

test: $(LIBNAME) testrunner.exe run_test

testrunner.exe: tests/main.cpp
	$(CC) $(CFLAGS) -I./ -L./ $^ -o $@ $(LIBS) -lstrings

run_test:
	cls
	testrunner

clean:
	del $(LIBNAME) libstrings.lib *.o *.gch testrunner.exe

install:
	copy /y $(LIBNAME) $(INSTALLDIR)
	 copy /y libstrings.lib $(INSTALLDIR)
	copy /y Strings.hpp $(INSTALLDIR)
