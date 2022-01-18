#Makefile gcc 9.3.0
objects = main.o fill.o trie.o wio.o

.PHONY: all
all: dictionary
dictionary: ${objects}
	gcc -o dictionary ${objects} -lstdc++

main.o:	fill.h trie.h wio.h
fill.o: fill.h trie.h
trie.o: trie.cpp trie.h
	gcc -c -o trie.o trie.cpp -std=c++2a
wio.o: wio.h

.PHONY: clean
clean:
	-rm -f dictionary *.o 2>/dev/null
