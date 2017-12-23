CFLAGS=-g -std=gnu99  -Wall -Werror
INCLUDE_FLAGS= -I. -Igen/
LIB_FLAGS=-L./lib

main: main.c parse.h libx.so
	gcc $(LIB_FLAGS) $(INCLUDE_FLAGS) $(CFLAGS)  main.c -o bin/main -lx
	global -u
	chmod u+x bin/main

libx.so: obj/list.o obj/htable.o
	gcc -shared -o lib/libx.so obj/*

obj/list.o: list.h list.c
	gcc $(CFLAGS) -c -fpic list.c -o obj/list.o

obj/htable.o: htable.h htable.c
	gcc $(CFLAGS) -c -fpic htable.c -o obj/htable.o



