INCLUDE_FLAGS= -I./include -Igen/
CFLAGS=-g -std=gnu99  -Wall -Werror $(INCLUDE_FLAGS)
LIB_CFLAGS= -c fpic
OBJ_DIR=obj
LIB_FLAGS=-L./lib

main: main.c include/parse.h libx.so
	gcc $(LIB_FLAGS) $(CFLAGS)  main.c -o bin/main -lx
	global -u
	chmod u+x bin/main

libx.so: $(OBJ_DIR)/list.o $(OBJ_DIR)/htable.o $(OBJ_DIR)/parse.o
	gcc -shared -o lib/$@ $^

$(OBJ_DIR)/list.o:  list.c include/list.h
	gcc $(CFLAGS) $(LIB_CFLAGS) $< -o $@

$(OBJ_DIR)/parse.o: parse.c include/parse.h 
	gcc $(CFLAGS) $(LIB_CFLAGS) $< -o $@

$(OBJ_DIR)/htable.o: htable.c include/htable.h 
	gcc $(CFLAGS) $(LIB_CFLAGS) $< -o $@





