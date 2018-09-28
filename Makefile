COMPILER = gcc
OPTIONS = -g -Wall -pedantic
LINKOPTIONS = -lcunit	

test_hash: hash_table.o hash_table_tests.c
	$(COMPILER) $(OPTIONS) hash_table.o hash_table_tests.c -o test_hash $(LINKOPTIONS)

test_list: linked_list.o linked_list_tests.c
	$(COMPILER) $(OPTIONS) linked_list.o linked_list_tests.c -o test_list $(LINKOPTIONS)

hash_table.o: hash_table.c hash_table.h
	$(COMPILER) $(OPTIONS) -c hash_table.c hash_table.h $(LINKOPTIONS)

linked_list.o: linked_list.c linked_list.h
	$(COMPILER) $(OPTIONS) -c linked_list.c linked_list.h $(LINKOPTIONS)

memtest: main
	valgrind --leak-check=full ./main

clean:
	rm *.o test_list test_hash

gitadd:
	git add *.c *.h Makefile


