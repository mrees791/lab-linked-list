all:
	gcc test.c linked_list.c linked_list.h -o test
clean:
	rm test
