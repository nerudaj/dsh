CC=g++
INSTALLDIR=C:\tools\utils
CFLAGS=-std=gnu++14 -Wall -Wextra -pedantic -I$(INSTALLDIR) -L$(INSTALLDIR)
LIBS=-lconfig -lstrings -llogger 
BINNAME=makegen.exe

all: $(BINNAME)

Makegen.o: Makegen.cpp Makegen.hpp
	$(CC) $(CFLAGS) $^ -c

$(BINNAME): Main.cpp Makegen.o 
	$(CC) $(CFLAGS) $(LIBS) $^ -o $@

clean:
	del $(BINNAME) *.o *.gch

install:
	copy /y $(BINNAME) $(INSTALLDIR)
