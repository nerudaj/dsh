CC=g++
INSTALLDIR=C:\tools\utils
CFLAGS=-std=gnu++14 -Wall -Wextra -pedantic -I$(INSTALLDIR) -L$(INSTALLDIR)
LIBS=
LIBNAME=liblogger.dll

all: $(LIBNAME)

Logger.o: Logger.cpp Logger.hpp
	$(CC) $(CFLAGS) -fPIC $^ -c

$(LIBNAME): Logger.o 
	$(CC) $(CFLAGS) -shared $(LIBS) $^ -o $@ -Wl,--out-implib,liblogger.lib

clean:
	del $(LIBNAME) liblogger.lib *.o *.gch testrunner.exe

install:
	copy /y $(LIBNAME) $(INSTALLDIR)
	 copy /y liblogger.lib $(INSTALLDIR)
	copy /y Logger.hpp $(INSTALLDIR)
