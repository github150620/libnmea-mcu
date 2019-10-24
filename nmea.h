/*
 * Reference:
 *   http://www.gpsinformation.org/dale/nmea.htm
 */
#ifndef _NMEA_H_
#define _NMEA_H_

#define NMEA_SENTENCE_LENGTH_MAX 82

typedef struct {
  char   status;    // 'A' - active, 'V' - Void
  char   date[6];   // YYMMDD(UTC)
  char   time[6];   // HHMMSS(UTC)
  double latitude;  // -90 ~ +90
  double longitude; // - 180 ~ +180
  double speed;     // km/h
  double heading;   // 0 ~ 359.99
}nmea_gprmc_t;

/* Example:
 *   $GPRMC,073601.00,A,2930.74875,N,10634.26655,E,2.592,181.57,231019,,,D*65\r\n
 */
int nmea_parse_gprmc(char *sentence, nmea_gprmc_t *rmc);

#endif
