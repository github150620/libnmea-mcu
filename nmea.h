/*
 * Reference:
 *   http://www.gpsinformation.org/dale/nmea.htm
 */
#ifndef _NMEA_H_
#define _NMEA_H_

#define SENTENCE_MAX_LENGTH 82

typedef struct {
  char   date[6]; // UTC Date, the format is YYMMDD.
  char   time[6]; // UTC Time, the format is HHMMSS.
  double latitude;
  double longitude;
  double speed;
  double heading;
}nmea_gprmc_t;

/* Example:
 *   $GPRMC,073601.00,A,2930.74875,N,10634.26655,E,2.592,181.57,231019,,,D*65\r\n
 */
int nmea_parse_gprmc(char *sentence, nmea_grmc_t *rmc);

#endif
