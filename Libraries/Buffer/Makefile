CC=g++
INSTALLDIR=C:\tools\utils
CFLAGS=-std=gnu++14 -Wall -Wextra -pedantic -I$(INSTALLDIR)
LIBNAME=Buffer.hpp

test: $(LIBNAME) testrunner.exe run_test

testrunner.exe: tests/main.cpp
	$(CC) $(CFLAGS) -I./ $^ -o $@

run_test:
	cls
	testrunner

install:
	copy /y $(LIBNAME) $(INSTALLDIR)

clean:
	del testrunner.exe