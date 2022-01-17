#Makefile
objects = main.o wio.o

.PHONY: all
all: dictionary
dictionary: ${objects}
	gcc -o dictionary ${objects} -lstdc++

main.o:	wio.h
wio.o: wio.h

.PHONY: clean
clean:
	-rm -f dictionary *.o 2>/dev/null
