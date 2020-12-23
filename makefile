all:
	gcc list_test.c linkedlist.c linkedlist.h -o list_test
clean:
	rm list_test
