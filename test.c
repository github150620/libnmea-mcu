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

    char s2[] = "$GPGGA,123519,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*47\r\n";
    nmea_gpgga_t gga;
    nmea_parse_gpgga(s2, &gga);

    printf("\n\n-------- sentence --------\n");
    printf("%s\n", s2);

    printf("-------- parse --------\n");
    printf("     time: %c%c%c%c%c%c\n",
        gga.time[0],
        gga.time[1],
        gga.time[2],
        gga.time[3],
        gga.time[4],
        gga.time[5]);
    printf(" latitude: %f\n", gga.latitude);
    printf("longitude: %f\n", gga.longitude);
    printf("  quality: %d\n", gga.quality);
    printf("    NoSBT: %d\n", gga.NoSBT);
    printf("     HDoP: %f\n", gga.HDoP);
    printf(" altitude: %f\n", gga.altitude);
    printf("      HoG: %f\n", gga.HoG);

    return 0;
}
