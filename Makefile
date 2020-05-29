all: libgol.so gameoflife

libgol.so: gol.o
	gcc gol.o -shared -Wall -Wextra -pedantic -std=c11 -o libgol.so

gol.o: gol.c
	gcc gol.c -c -fPIC -Wall -Wextra -pedantic -std=c11 -o gol.o

gameoflife.o: gameoflife.c
	gcc gameoflife.c -c -fPIC -Wall -Wextra -pedantic -std=c11 -o gameoflife.o

gameoflife: gameoflife.o
	gcc gameoflife.o -fPIC -L. -lgol -Wall -Wextra -pedantic -std=c11 -o gameoflife

clean:
	rm gameoflife.o
	rm gameoflife
	rm gol.o
	rm libgol.so
