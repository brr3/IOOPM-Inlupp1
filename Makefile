COMPILER = gcc
OPTIONS = -g -Wall -pedantic
LINKOPTIONS = -lcunit


hash_table.o: hash_table.c hash_table.h
	$(COMPILER) $(OPTIONS) -c hash_table.c hash_table.h $(LINKOPTIONS)	

main: hash_table.o main.c
	$(COMPILER) $(OPTIONS) hash_table.o main.c -o main $(LINKOPTIONS) 

linked_list.o: linked_list.c linked_list.h
	$(COMPILER) $(OPTIONS) -c linked_list.c linked_list.h $(LINKOPTIONS)

memtest: main
	valgrind --leak-check=full ./main;

clean:
	rm *.o main

gitadd:
	git add *.c *.h Makefile

