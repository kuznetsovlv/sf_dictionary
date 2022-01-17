#Makefile
objects = main.o trie.o wio.o

.PHONY: all
all: dictionary
dictionary: ${objects}
	gcc -o dictionary ${objects} -lstdc++

main.o:	trie.h wio.h
tire.o: trie.h
wio.o: wio.h

.PHONY: clean
clean:
	-rm -f dictionary *.o 2>/dev/null
