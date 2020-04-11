#ifndef _NMEA_COMMON_H_
#define _NMEA_COMMON_H_

int nmea_parse_latitude(char *s, int len, double *latitude);
int nmea_parse_longitude(char *s, int len, double *longitude);
int nmea_parse_double(char *s, int len, double *d);

#endif
