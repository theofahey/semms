all: control.o write.o
	gcc -o control semap.o
	gcc -o write writing.o
semap.o: semap.c
	gcc -c semap.c
writing.o: writing.c
	gcc -c writing.c


