COMPILER = gcc
OPTIONS = -g -Wall -pedantic
LINKOPTIONS = -lcunit	

test_hash: hash_table.o linked_list.o hash_table_tests.c
	$(COMPILER) $(OPTIONS) hash_table.o hash_table_tests.c linked_list.o -o test_hash $(LINKOPTIONS)

test_list: linked_list.o linked_list_tests.o
	$(COMPILER) $(OPTIONS) linked_list.o linked_list_tests.o -o test_list $(LINKOPTIONS)

test_iterator: linked_list.o iterator.h iterator_tests.c
	$(COMPILER) $(OPTIONS) linked_list.o iterator.h iterator_tests.c -o test_iterator $(LINKOPTIONS)

hash_table.o: hash_table.c hash_table.h
	$(COMPILER) $(OPTIONS) -c hash_table.c hash_table.h $(LINKOPTIONS)

linked_list.o: linked_list.c linked_list.h
	$(COMPILER) $(OPTIONS) -c linked_list.c linked_list.h $(LINKOPTIONS)

linked_list_tests.o: linked_list_tests.c
	$(COMPILER) $(OPTIONS) -c linked_list_tests.c $(LINKOPTIONS)

iterator.o: linked_list.c iterator.h
	$(COMPILER) $(OPTIONS) -c linked_list.c iterator.h $(LINKOPTIONS)

fulltest: test_list test_hash
	./test_list
	./test_hash
	./test_iterator

memtest_list: test_list
	valgrind --leak-check=full ./test_list

memtest_hash: test_hash
	valgrind --leak-check=full ./test_hash

clean:
	rm *.o test_list test_hash

gitadd:
	git add *.c *.h Makefile

