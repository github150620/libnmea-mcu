CC := gcc
OBJECTS := test.o nmea_common.o nmea_gprmc.o

test:
	$(cc) -o test $(OBJECTS)

%.o: %.c
	$(cc) -c -o $@ $<

.PHONY: clean
clean:
	rm -rf *.o test
