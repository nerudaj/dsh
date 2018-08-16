CC=g++
INSTALLDIR=C:\tools\utils
CFLAGS=-Wall -Wextra -pedantic -I$(INSTALLDIR) -L$(INSTALLDIR)
LIBNAME=logger.a
all: $(LIBNAME)

Logger.o: Logger.cpp Logger.hpp
	$(CC) $(CFLAGS) $^ -c

$(LIBNAME): Logger.o 
	ar rvs $@ $^

clean:
	del $(LIBNAME) *.o *.gch

install:
	copy /y $(LIBNAME) $(INSTALLDIR)
	copy /y Logger.hpp $(INSTALLDIR)
