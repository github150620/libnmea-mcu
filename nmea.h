/*
 * Reference:
 *   http://www.gpsinformation.org/dale/nmea.htm
 */
#ifndef _NMEA_H_
#define _NMEA_H_

#define NMEA_SENTENCE_LENGTH_MAX 82

// $GPGGA,123519,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*47
typedef struct {
  char   time[6];   // HHMMSS(UTC)
  double latitude;  // -90 ~ +90
  double longitude; // - 180 ~ +180
  int    quality;   // 0 ~ 8
  int    NoSBT;     // Number of satellites being tracked
  double altitude;  // Altitude, Meters, above mean sea level
  double HoG;       // Height of geoid (mean sea level) above WGS84 ellipsoid
}nmea_gpgga_t;

// $GPGLL,4916.45,N,12311.12,W,225444,A,*1D
typedef struct {
  double latitude;
  double longitude;
  char   time[6];   // HHMMSS(UTC)
  char   status;    // 'A' - active, 'V' - Void
}nmea_gpgll_t;

// $GPGSV,2,1,08,01,40,083,46,02,17,308,41,12,07,344,39,14,22,228,45*75
typedef struct {
  int NoSfFD;     // Number of sentences for full data
  int index;      // sentence 1 of 2
  int NoSIV;      // Number of satellites in view
  int PRN;        // Satellite PRN number
  int elevation;  // Elevation, degrees
  int azimuth;    // Azimuth, degrees
  int SNR;        // SNR - higher is better for up to 4 satellites per sentence
}nmea_gpgsv_t;

// $GPRMC,073601.00,A,2930.74875,N,10634.26655,E,2.592,181.57,231019,,,D*65\r\n
typedef struct {
  char   status;    // 'A' - active, 'V' - Void
  char   date[6];   // YYMMDD(UTC)
  char   time[6];   // HHMMSS(UTC)
  double latitude;  // -90 ~ +90
  double longitude; // - 180 ~ +180
  double speed;     // km/h
  double heading;   // 0 ~ 359.99
}nmea_gprmc_t;

// $GPVTG,054.7,T,034.4,M,005.5,N,010.2,K*48
typedef struct {
  double ttmg;  // True track made good (degrees)
  double mtmg;  // Magnetic track made good
  double knots; // Ground speed, knots
  double kmph;  // Ground speed, Kilometers per hour
}nmea_gpvtg_t;

int nmea_parse_gpgga(char *sentence, nmea_gpgga_t *gga);
int nmea_parse_gpgll(char *sentence, nmea_gpgll_t *gll);
int nmea_parse_gpgsv(char *sentence, nmea_gpgsv_t *gsv);
int nmea_parse_gprmc(char *sentence, nmea_gprmc_t *rmc);
int nmea_parse_gpvtg(char *sentence, nmea_gpvtg_t *vtg);

#endif
