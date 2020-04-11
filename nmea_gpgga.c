#include "nmea.h"
#include <stdint.h>
#include <string.h>

/* Example:
 *   $GPGGA,123519,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*47
 */

int nmea_parse_gpgga(char *sentence, nmea_gprmc_t *gga) {
  char *p;
  int i;
  int j = 0;
  
  uint8_t comma_position[14];
  uint8_t asterisk_position;
  
  for (i=0; i<NMEA_SENTENCE_LENGTH_MAX; i++) {
    if (sentence[i] == '\0') break;
    
    if (sentence[i] == ',') {
      comma_position[j++] = i;
    }

    if (sentence[i] == '*') {
      asterisk_position = i;
    }
  }
  
  // There must be 14 commas in a GGA sentence.
  if (j != 14) {
    return -1;
  }

  if (strncmp(sentence, "$GPGGA", comma_position[0] - 0) != 0) {
    return -1;
  }  

  // time
  if (comma_position[1] - comma_position[0] == 1) {
    gga->time[0] = '\0';
  } else if (comma_position[1] - comma_position[0] >= 7) {
    memcpy(gga->time, &sentence[comma_position[0]+1], 6);
  } else {
    return -1;
  }

  // Latitude
  if (comma_position[2] - comma_position[1] == 1) {
    rmc->latitude = 0.0;
  } else if (comma_position[2] - comma_position[1] >= 9) {
    p = &sentence[comma_position[1]+1];
    rmc->latitude = 0.0;
    rmc->latitude += (p[0] - '0') * 10;
    rmc->latitude += (p[1] - '0') * 1;
    rmc->latitude += (p[2] - '0') / 6.0;
    rmc->latitude += (p[3] - '0') / 60.0;
    if (p[4] != '.') return -1;
    rmc->latitude += (p[5] - '0') / 600.0;
    rmc->latitude += (p[6] - '0') / 6000.0;
    rmc->latitude += (p[7] - '0') / 60000.0;
    if (comma_position[3] - comma_position[2] >= 11) {
      rmc->latitude += (p[8] - '0') / 600000.0;
      rmc->latitude += (p[9] - '0') / 6000000.0;
    }
  } else {
    return -1;
  }

  if (comma_position[3] - comma_position[2] == 1) {
    rmc->latitude = 0.0;
  } else if (comma_position[3] - comma_position[2] == 2) {
    switch (sentence[comma_position[2]+1])
    {
    case 'N':
      rmc->latitude *= 1.0;
      break;
    case 'S':
      rmc->latitude *= -1.0;
      break;
    default:
      return -1;
    }
  } else {
    return -1;
  }

  // Longitude
  if (comma_position[4] - comma_position[3] == 1) {
    rmc->longitude = 0.0;
  } else if (comma_position[4] - comma_position[3] >= 10) {
    p = &sentence[comma_position[3]+1];
    rmc->longitude = 0.0;
    rmc->longitude += (p[0] - '0') * 100;
    rmc->longitude += (p[1] - '0') * 10;
    rmc->longitude += (p[2] - '0') * 1;
    rmc->longitude += (p[3] - '0') / 6.0;
    rmc->longitude += (p[4] - '0') / 60.0;
    if (p[5] != '.') return -1;
    rmc->longitude += (p[6] - '0') / 600.0;
    rmc->longitude += (p[7] - '0') / 6000.0;
    rmc->longitude += (p[8] - '0') / 60000.0;
    if (comma_position[5] - comma_position[4] >= 12) {
      rmc->longitude += (p[9] - '0') / 600000.0;
      rmc->longitude += (p[10] - '0') / 6000000.0;
    }
  } else {
    return -1;
  }

  if (comma_position[5] - comma_position[4] == 1) {
    rmc->longitude = 0.0;
  } else if (comma_position[5] - comma_position[4] == 2) {
    switch (sentence[comma_position[4]+1])
    {
    case 'E':
      rmc->longitude *= 1.0;
      break;
    case 'W':
      rmc->longitude *= -1.0;
      break;
    default:
      return -1;
    }
  } else {
    return -1;
  }

  ...
  
  return 0;
}
