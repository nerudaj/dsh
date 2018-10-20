CC=g++
CFLAGS=-std=gnu++14 -Wall -Wextra -pedantic

all: buffer.exe

buffer.exe: main.cpp
	$(CC) $(CFLAGS) $^ -o $@

clean:
	del /y buffer.exe