CC=g++
INSTALLDIR=C:\tools\utils
CFLAGS=-Wall -Wextra -pedantic -I$(INSTALLDIR) -L$(INSTALLDIR)
BINNAME=makegen.exe
LIBS=-lconfig -lstrings

all: $(BINNAME)

Makegen.o: Makegen.cpp Makegen.hpp
	$(CC) $(CFLAGS) $^ -c

$(BINNAME): Main.cpp Makegen.o 
	$(CC) $(CFLAGS) $(LIBS) $^ -o $@

clean:
	del $(BINNAME) *.o *.gch

install:
	copy /y $(BINNAME) $(INSTALLDIR)
