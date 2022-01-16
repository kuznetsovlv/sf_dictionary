#Makefile
objects = main.o

.PHONY: all
all: dictionary
dictionary: ${objects}
	gcc -o dictionary ${objects} -lstdc++

main.o:

.PHONY: clean
clean:
	-rm -f dictionary *.o 2>/dev/null
