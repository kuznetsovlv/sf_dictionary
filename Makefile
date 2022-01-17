#Makefile
objects = main.o trie.o wio.o

.PHONY: all
all: dictionary
dictionary: ${objects}
	gcc -o dictionary ${objects} -lstdc++

main.o:	trie.h wio.h
trie.o: trie.cpp trie.h
	gcc -c -o trie.o trie.cpp -std=c++2a
wio.o: wio.h

.PHONY: clean
clean:
	-rm -f dictionary *.o 2>/dev/null
