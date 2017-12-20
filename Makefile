table: table.c list.h
	gcc -I./. -std=gnu99  table.c -o table
	chmod u+x table
	./table
