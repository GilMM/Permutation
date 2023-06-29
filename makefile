permut:  mypermut.o
	gcc -g -Wall -ansi -pedantic permut.c -o mypermut -lm
mypermut.o:  permut.c
	gcc -c -Wall -ansi -pedantic permut.c -o mypermut.o -lm
