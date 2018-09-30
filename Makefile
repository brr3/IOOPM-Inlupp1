COMPILER = gcc
OPTIONS = -g -Wall -pedantic
LINKOPTIONS = -lcunit	

test_hash: hash_table.o hash_table_tests.c
	$(COMPILER) $(OPTIONS) hash_table.o hash_table_tests.c -o test_hash $(LINKOPTIONS)

test_list: linked_list.o linked_list_tests.o
	$(COMPILER) $(OPTIONS) linked_list.o linked_list_tests.o -o test_list $(LINKOPTIONS)

hash_table.o: hash_table.c hash_table.h
	$(COMPILER) $(OPTIONS) -c hash_table.c hash_table.h $(LINKOPTIONS)

linked_list.o: linked_list.c linked_list.h
	$(COMPILER) $(OPTIONS) -c linked_list.c linked_list.h $(LINKOPTIONS)

linked_list_tests.o: linked_list_tests.c
	$(COMPILER) $(OPTIONS) -c linked_list_tests.c $(LINKOPTIONS)

fulltest: test_list test_hash
	./test_list
	./test_hash

memtest_list: test_list
	valgrind --leak-check=full ./test_list

memtest_hash: test_hash
	valgrind --leak-check=full ./test_hash

clean:
	rm *.o test_list test_hash

gitadd:
	git add *.c *.h Makefile

