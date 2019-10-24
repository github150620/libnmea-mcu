all: test

nmea.o: nmea.c
	gcc -c nmea.c

test.o: test.c
	gcc -c test.c

test: nmea.o test.o
	gcc -o test nmea.o test.o

clean:
	rm -rf test.o nmea.o test
