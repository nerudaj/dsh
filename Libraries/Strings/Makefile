CC=g++
INSTALLDIR=C:\tools\utils
CFLAGS=-std=gnu++14 -Wall -Wextra -pedantic
LIBNAME=libstrings.dll

all: $(LIBNAME)

Strings.o: Strings.cpp Strings.hpp
	$(CC) $(CFLAGS) -fPIC $^ -c

$(LIBNAME): Strings.o 
	$(CC) $(CFLAGS) -shared $^ -o $@

test: $(LIBNAME) testrunner.exe run_test

testrunner.exe: tests/main.cpp
	$(CC) $(CFLAGS) -I./ -L./ $^ -o $@ $(LIBS) -l:./$(LIBNAME)

run_test:
	cls
	testrunner

clean:
	del $(LIBNAME) *.o *.gch testrunner.exe

install:
	copy /y $(LIBNAME) $(INSTALLDIR)
	copy /y Strings.hpp $(INSTALLDIR)
