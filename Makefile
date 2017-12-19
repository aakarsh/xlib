table: table.c
	gcc -I ./ -std=gnu99  table.c -o table
	chmod u+x table
	./table
