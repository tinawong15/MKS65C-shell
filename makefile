all: main.o shell.o prompt.o
	gcc main.o shell.o prompt.o

main.o: main.c
	gcc -c -g main.c

shell.o: shell.c shell.h
	gcc -c -g shell.c

prompt.o: prompt.c prompt.h
	gcc -c -g prompt.c

run:
	./a.out $(args)

clean:
	rm -rf *.o a.out
