CC=g++
INSTALLDIR=C:\tools\utils
CFLAGS=-Wall -Wextra -pedantic -I$(INSTALLDIR) -L$(INSTALLDIR)
LIBS=-lconfig -lstrings -llogger 
BINNAME=hexrgb.exe

all: $(BINNAME)

$(BINNAME): Main.cpp 
	$(CC) $(CFLAGS) $(LIBS)  $^ -o $@

clean:
	del $(BINNAME) *.o *.gch

install:
	copy /y $(BINNAME) $(INSTALLDIR)
