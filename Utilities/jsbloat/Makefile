CC=g++
INSTALLDIR=C:\tools\utils
CFLAGS=-std=gnu++14 -Wall -Wextra -pedantic -I$(INSTALLDIR) -L$(INSTALLDIR)
LIBS=-lconfig -lstrings -llogger 
BINNAME=jsbloat.exe

all: $(BINNAME)

$(BINNAME): Main.cpp 
	$(CC) $(CFLAGS) $(LIBS) $^ -o $@

clean:
	del $(BINNAME) *.o *.gch

install:
	copy /y $(BINNAME) $(INSTALLDIR)
