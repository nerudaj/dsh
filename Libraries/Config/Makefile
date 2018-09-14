CC=g++
INSTALLDIR=C:\tools\utils
CFLAGS=-Wall -Wextra -pedantic -I$(INSTALLDIR) -L$(INSTALLDIR)
LIBS=-llogger -lstrings 
LIBNAME=libconfig.dll

all: $(LIBNAME)

Ini.o: Ini.cpp Ini.hpp
	$(CC) $(CFLAGS) -fPIC $^ -c

Args.o: Args.cpp Args.hpp
	$(CC) $(CFLAGS) -fPIC $^ -c

Item.o: Item.cpp Item.hpp
	$(CC) $(CFLAGS) -fPIC $^ -c

Csv.o: Csv.cpp Csv.hpp
	$(CC) $(CFLAGS) -fPIC $^ -c

$(LIBNAME): Ini.o Args.o Item.o Csv.o 
	$(CC) $(CFLAGS) -shared $(LIBS)  $^ -o $@

clean:
	del $(LIBNAME) *.o *.gch

install:
	copy /y $(LIBNAME) $(INSTALLDIR)
	copy /y Config.hpp $(INSTALLDIR)
	copy /y Ini.hpp $(INSTALLDIR)
	copy /y Args.hpp $(INSTALLDIR)
	copy /y Item.hpp $(INSTALLDIR)
	copy /y Csv.hpp $(INSTALLDIR)
