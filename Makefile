CC=clang

# HashTable
hashtable: hashtable.o
	ar rcs lib/libhashtable.a lib/hashtable.o

hashtable.o: src/hashtable.c
	$(CC) -c -o lib/hashtable.o $<

