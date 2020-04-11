# libnmea-mcu
C library for parsing NMEA 0183. It is designed for MCU and also can be used for PC.

## How to use
Copy ```nmea_common.c```, ```nmea_common.h```, ```nmea_gprmc.c``` and ```nmea.h``` to your project, and write code like follows.
```
#include "nmea.h"
#include <stdio.h>

int main() {
    char s[] = "$GPRMC,073601.00,A,2930.74875,N,10634.26655,E,2.592,181.57,231019,,,D*65\r\n";
    nmea_gprmc_t rmc;
    nmea_parse_gprmc(s, &rmc);

    printf("-------- sentence --------\n");
    printf("%s\n", s);

    printf("-------- parse --------\n");
    printf("     time: %c%c%c%c%c%c\n",
        rmc.time[0],
        rmc.time[1],
        rmc.time[2],
        rmc.time[3],
        rmc.time[4],
        rmc.time[5]);
    printf(" latitude: %f\n", rmc.latitude);
    printf("longitude: %f\n", rmc.longitude);
    printf("    speed: %f\n", rmc.speed);
    printf("  heading: %f\n", rmc.heading);
    printf("     date: %c%c%c%c%c%c\n",
        rmc.date[0],
        rmc.date[1],
        rmc.date[2],
        rmc.date[3],
        rmc.date[4],
        rmc.date[5]);
    return 0;
}
```

## Reference
http://www.gpsinformation.org/dale/nmea.htm

## Contact Me
E-mail: 597540267@qq.com
