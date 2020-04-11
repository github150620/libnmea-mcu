CC := gcc
OBJECTS := test.o nmea_common.o nmea_gprmc.o

test: $(OBJECTS)
	$(CC) -o test $(OBJECTS)

%.o: %.c
	$(CC) -c -o $@ $<

.PHONY: clean
clean:
	rm -rf *.o test
