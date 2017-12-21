table: table.c list.h htable.h
	gcc -g  -I./. -std=gnu99  table.c -o bin/table
	global -u
	chmod u+x bin/table

