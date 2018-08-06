CC=g++
INSTALLDIR=C:\tools\utils
CFLAGS=-Wall -Wextra -pedantic -I$(INSTALLDIR) -L$(INSTALLDIR)
LIBNAME=liblogger.dll
all: $(LIBNAME)

Logger.o: Logger.cpp Logger.hpp
	$(CC) $(CFLAGS) -fPIC $^ -c

$(LIBNAME): Logger.o 
	$(CC) -shared $^ -o $@

clean:
	del $(LIBNAME) *.o *.gch

install:
	copy /y $(LIBNAME) $(INSTALLDIR)
	copy /y Logger.hpp $(INSTALLDIR)
