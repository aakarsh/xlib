INCLUDE_FLAGS= -I./include -Igen/
CFLAGS=-g -std=gnu99  -Wall -Werror $(INCLUDE_FLAGS) -lm 
LIB_CFLAGS= -c -fpic -lm -lrary
OBJ_DIR=obj
SRC_DIR=src
TEST_DIR=test
BIN_DIR=bin
LIB_FLAGS=-L./lib

main: $(SRC_DIR)/main.c include/parse.h libx.so
	gcc $(LIB_FLAGS) $(CFLAGS)  $< -o $(BIN_DIR)/main -lx
	global -u
	chmod u+x $(BIN_DIR)/main

libx.so: $(OBJ_DIR)/list.o $(OBJ_DIR)/htable.o $(OBJ_DIR)/parse.o $(OBJ_DIR)/heap.o
	gcc -shared -o lib/$@ $^

$(OBJ_DIR)/heap.o: $(SRC_DIR)/heap.c include/heap.h
	gcc $(CFLAGS) $(LIB_CFLAGS) $< -o $@

$(OBJ_DIR)/list.o: $(SRC_DIR)/list.c include/list.h
	gcc $(CFLAGS) $(LIB_CFLAGS) $< -o $@

$(OBJ_DIR)/parse.o: $(SRC_DIR)/parse.c include/parse.h 
	gcc $(CFLAGS) $(LIB_CFLAGS) $< -o $@

$(OBJ_DIR)/htable.o: $(SRC_DIR)/htable.c include/htable.h 
	gcc $(CFLAGS) $(LIB_CFLAGS) $< -o $@

