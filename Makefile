CFLAGS=-g -std=gnu99  -Wall -Werror
INCLUDE_FLAGS= -I./include -Igen/
LIB_FLAGS=-L./lib

main: main.c include/parse.h libx.so
	gcc $(LIB_FLAGS) $(INCLUDE_FLAGS) $(CFLAGS)  main.c -o bin/main -lx
	global -u
	chmod u+x bin/main

libx.so: obj/list.o obj/htable.o
	gcc -shared -o lib/libx.so obj/*

obj/list.o: include/list.h list.c
	gcc $(CFLAGS) -c -fpic list.c -o obj/list.o

obj/htable.o: include/htable.h htable.c
	gcc $(INCLUDE_FLAGS) $(CFLAGS) -c -fpic htable.c -o obj/htable.o



