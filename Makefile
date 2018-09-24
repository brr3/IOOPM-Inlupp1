hash_table.o: hash_table.c hash_table.h
	gcc -g -c -Wall hash_table.c

main: hash_table.o main.c
	gcc -g hash_table.o main.c -o main -lcunit

memtest: main
	valgrind --leak-check=full ./main
