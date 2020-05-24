all: build run clean

lab6c.o: main.c
	gcc -c -o lab6c.o main.c

build: lab6c.o
	gcc -o lab6c lab6c.o
	
run:
	lab6c.exe

clean:
	del *.o lab6c
	del lab6c.exe lab6c