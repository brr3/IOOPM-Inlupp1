COMPILER = gcc
OPTIONS = -g
LINKOPTIONS = -lcunit -pg

test_hash: hash_table.o linked_list.o hash_table_tests.c
	$(COMPILER) $(OPTIONS) hash_table.o hash_table_tests.c linked_list.o -o test_hash $(LINKOPTIONS)

test_list: linked_list.o linked_list_tests.c
	$(COMPILER) $(OPTIONS) linked_list.o linked_list_tests.c -o test_list $(LINKOPTIONS)

hash_table.o: hash_table.c hash_table.h
	$(COMPILER) $(OPTIONS) -c hash_table.c hash_table.h $(LINKOPTIONS)

linked_list.o: linked_list.c linked_list.h
	$(COMPILER) $(OPTIONS) -c linked_list.c linked_list.h $(LINKOPTIONS)

fulltest: test_list test_hash
	./test_list
	./test_hash

memtest_list: test_list
	valgrind --leak-check=full ./test_list

memtest_hash: test_hash
	valgrind --leak-check=full ./test_hash

clean:
	rm *.o *.h.gch *.out *.gcno *.gcda *.gcov test_list test_hash freq_count

gitadd:
	git add *.c *.h *.md Makefile

freq_count: freq_count.c linked_list.o hash_table.o
	$(COMPILER) $(OPTIONS) hash_table.o freq_count.c linked_list.o -o freq_count $(LINKOPTIONS)

hash_cov: hash_table.o linked_list.o hash_table_tests.c
	$(COMPILER) $(OPTIONS) --coverage hash_table.c hash_table_tests.c linked_list.o -o test_hash $(LINKOPTIONS)
	./test_hash
	gcov -abcfu hash_table.c

list_cov: linked_list.o linked_list_tests.c
	$(COMPILER) $(OPTIONS) --coverage linked_list.c linked_list_tests.c -o test_list $(LINKOPTIONS)
	./test_list
	gcov -abcfu linked_list.c
