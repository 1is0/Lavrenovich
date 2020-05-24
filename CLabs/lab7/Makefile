CC = gcc

all: build run clean
	
main.o: main.c
	$(CC) -O0 -g3 -Wall -c main.c

MusDir.o: MusDir.h MusDir.c
	$(CC) -O0 -g3 -Wall -c MusDir.h MusDir.c

Musician.o: Musician.h Musician.c
	$(CC) -O0 -g3 -Wall -c Musician.h Musician.c
	
Album.o: Album.h Album.c
	$(CC) -O0 -g3 -Wall -c Album.h Album.c
	
Song.o: Song.h Song.c
	$(CC) -O0 -g3 -Wall -c Song.h Song.c
	
Basket.o: Basket.h Basket.c
	$(CC) -O0 -g3 -Wall -c Basket.h Basket.c
	
build: main.o MusDir.o Musician.o Album.o Song.o Basket.o
	$(CC) -o lab7c main.o MusDir.o Musician.o Album.o Song.o Basket.o
	
run: 
	lab7c.exe
	
clean:
	del *.o lab7c
	del lab7c.exe lab7c
	del *.gch lab7c