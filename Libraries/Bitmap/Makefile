CC=g++
INSTALLDIR=C:\tools\utils
CFLAGS=-Wall -Wextra -pedantic -I$(INSTALLDIR) -L$(INSTALLDIR)
LIBS=-llogger 
LIBNAME=libbitmap.dll

all: $(LIBNAME)

Bitmap.o: Bitmap.cpp Bitmap.hpp
	$(CC) $(CFLAGS) -fPIC $^ -c

$(LIBNAME): Bitmap.o 
	$(CC) $(CFLAGS) -shared $(LIBS)  $^ -o $@

clean:
	del $(LIBNAME) *.o *.gch

install:
	copy /y $(LIBNAME) $(INSTALLDIR)
	copy /y Bitmap.hpp $(INSTALLDIR)
