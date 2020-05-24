all: build run clean

lab5c.o: main.c
	gcc -c -o lab5c.o main.c

build: lab5c.o
	gcc -o lab5c lab5c.o
	
run:
	lab5c.exe

clean:
	del *.o lab5c
	del lab5c.exe lab5c