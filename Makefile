all: test

nmea_common.o: nmea_common.c
	gcc -c nmea_common.c

nmea_gprmc.o: nmea_gprmc.c
	gcc -c nmea_gprmc.c

test.o: test.c
	gcc -c test.c

test: nmea_common.o nmea_gprmc.o test.o
	gcc -o test nmea_common.o nmea_gprmc.o test.o

clean:
	rm -rf *.o test
