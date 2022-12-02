image.o: image.c ../include/image.h
	gcc -c image.c -I../include -Wall -O2

libimage.a: image.o
	ar rvs libimage.a image.o

clean:
	rm image.o libimage.a
