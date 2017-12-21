table: table.c list.h htable.h
	gcc -g -I./. -std=gnu99  table.c -o table
	global -u
	chmod u+x table

