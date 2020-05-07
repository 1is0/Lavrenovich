lab5c.exe:	main.o
	gcc -o lab5c.exe main.o

main.o:	main.c
	gcc -O0 -g3 -Wall -c main.c
	gcc -masm=intel -g3 -Wall -c main.c -S
