CC=g++
CFLAGS=-Wall -Wextra -pedantic
LIBNAME=libconfig.dll
INSTALLDIR=C:\tools\libs

all: $(LIBNAME)

ConfigItem.o: ConfigItem.cpp ConfigItem.hpp
	$(CC) $(CFLAGS) -fPIC $^ -c

Config.o: Config.cpp Config.hpp
	$(CC) $(CFLAGS) -fPIC $^ -c

$(LIBNAME): Config.o ConfigItem.o
	$(CC) -shared $^ -o $@

clean:
	del -y *.o *.gch $(LIBNAME)

install:
	copy /y ConfigItem.hpp $(INSTALLDIR)
	copy /y Config.hpp $(INSTALLDIR)
	copy /y $(LIBNAME) $(INSTALLDIR)