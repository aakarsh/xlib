xlib: main.c list.h htable.h parse.h
	gcc -g  -I./. -std=gnu99  main.c -o bin/main
	global -u
	chmod u+x bin/main

