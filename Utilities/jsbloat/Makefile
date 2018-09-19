CC=g++
INSTALLDIR=C:\tools\utils
CFLAGS=-Wall -Wextra -pedantic -I$(INSTALLDIR) -L$(INSTALLDIR)
LIBS=-lconfig -lstrings 
STATICS=-Wl,--whole-archive $(INSTALLDIR)\-llogger -Wl,--no-whole-archive
BINNAME=jsbloat.exe

all: $(BINNAME)

$(BINNAME): Main.cpp 
	$(CC) $(CFLAGS) $(LIBS) $(STATICS)  $^ -o $@

clean:
	del $(BINNAME) *.o *.gch

install:
	copy /y $(BINNAME) $(INSTALLDIR)
