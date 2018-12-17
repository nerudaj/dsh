CC=g++
INSTALLDIR=C:\tools\utils
CFLAGS=-std=gnu++14 -Wall -Wextra -pedantic -I$(INSTALLDIR) -L$(INSTALLDIR)
LIBS=-llogger -lstrings 
LIBNAME=libconfig.dll

all: $(LIBNAME)

Ini.o: Ini.cpp
	$(CC) $(CFLAGS) -fPIC $^ -c

Args.o: Args.cpp
	$(CC) $(CFLAGS) -fPIC $^ -c

Item.o: Item.cpp
	$(CC) $(CFLAGS) -fPIC $^ -c

Csv.o: Csv.cpp
	$(CC) $(CFLAGS) -fPIC $^ -c

$(LIBNAME): Ini.o Args.o Item.o Csv.o 
	$(CC) $(CFLAGS) -shared $(LIBS) $^ -o $@ -Wl,--out-implib,libconfig.lib

test: $(LIBNAME) testrunner.exe run_test

testrunner.exe: tests/main.cpp
	$(CC) $(CFLAGS) -I./ -L./ $^ -o $@ $(LIBS) -lconfig

run_test:
	cls
	testrunner

clean:
	del $(LIBNAME) libconfig.lib *.o *.gch testrunner.exe

install:
	copy /y $(LIBNAME) $(INSTALLDIR)
	 copy /y libconfig.lib $(INSTALLDIR)
	copy /y Config.hpp $(INSTALLDIR)
	copy /y Ini.hpp $(INSTALLDIR)
	copy /y Args.hpp $(INSTALLDIR)
	copy /y Item.hpp $(INSTALLDIR)
	copy /y Csv.hpp $(INSTALLDIR)
