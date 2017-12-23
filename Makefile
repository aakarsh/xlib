libx.so: list.o htable.o
	gcc -shared -o lib/libx.so list.o htable.o

list.o: list.h list.c
	gcc -std=gnu99 -g -c -Wall -Werror -fpic list.c

htable.o: htable.h htable.c
	gcc -std=gnu99 -g -c -Wall -Werror -fpic htable.c

main: main.c parse.h libx.so
	gcc -L./lib -g -I./. -std=gnu99  main.c -o bin/main -lx
	global -u
	chmod u+x bin/main

