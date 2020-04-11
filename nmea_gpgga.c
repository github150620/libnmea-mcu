#include "nmea.h"
#include <stdint.h>
#include <string.h>

/* Example:
 *   $GPGGA,123519,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*47
 */

int nmea_parse_gpgga(char *sentence, nmea_gpgga_t *gga) {
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
    gga->latitude = 0.0;
  } else if (comma_position[2] - comma_position[1] >= 9) {
    p = &sentence[comma_position[1]+1];
    gga->latitude = 0.0;
    gga->latitude += (p[0] - '0') * 10;
    gga->latitude += (p[1] - '0') * 1;
    gga->latitude += (p[2] - '0') / 6.0;
    gga->latitude += (p[3] - '0') / 60.0;
    if (p[4] != '.') return -1;
    gga->latitude += (p[5] - '0') / 600.0;
    gga->latitude += (p[6] - '0') / 6000.0;
    gga->latitude += (p[7] - '0') / 60000.0;
    if (comma_position[2] - comma_position[1] >= 11) {
      gga->latitude += (p[8] - '0') / 600000.0;
      gga->latitude += (p[9] - '0') / 6000000.0;
    }
  } else {
    return -1;
  }

  if (comma_position[3] - comma_position[2] == 1) {
    gga->latitude = 0.0;
  } else if (comma_position[3] - comma_position[2] == 2) {
    switch (sentence[comma_position[2]+1])
    {
    case 'N':
      gga->latitude *= 1.0;
      break;
    case 'S':
      gga->latitude *= -1.0;
      break;
    default:
      return -1;
    }
  } else {
    return -1;
  }

  // Longitude
  if (comma_position[4] - comma_position[3] == 1) {
    gga->longitude = 0.0;
  } else if (comma_position[4] - comma_position[3] >= 10) {
    p = &sentence[comma_position[3]+1];
    gga->longitude = 0.0;
    gga->longitude += (p[0] - '0') * 100;
    gga->longitude += (p[1] - '0') * 10;
    gga->longitude += (p[2] - '0') * 1;
    gga->longitude += (p[3] - '0') / 6.0;
    gga->longitude += (p[4] - '0') / 60.0;
    if (p[5] != '.') return -1;
    gga->longitude += (p[6] - '0') / 600.0;
    gga->longitude += (p[7] - '0') / 6000.0;
    gga->longitude += (p[8] - '0') / 60000.0;
    if (comma_position[4] - comma_position[3] >= 12) {
      gga->longitude += (p[9] - '0') / 600000.0;
      gga->longitude += (p[10] - '0') / 6000000.0;
    }
  } else {
    return -1;
  }

  switch (comma_position[5] - comma_position[4]) {
    case 1:
      gga->longitude = 0.0;
      break;
    case 2:
      switch (sentence[comma_position[4]+1]) {
        case 'E':
          gga->longitude *= 1.0;
          break;
        case 'W':
          gga->longitude *= -1.0;
          break;
        default:
          return -1;
      }
      break;
    default:
      return -1;
  }

  // quality
  switch (comma_position[6] - comma_position[5]) {
    case 1:
      gga->quality = 0;
      break;
    case 2:
      gga->quality = sentence[comma_position[5]+1] - '0';
      break;
    default:
      return -1;
  }
  
  // Number of satellites being tracked
  switch (comma_position[7] - comma_position[6]) {
    case 2:
      gga->NoSBT = sentence[comma_position[6]+1] - '0';
      gga->NoSBT = gga->NoSBT * 10 + (sentence[comma_position[6]+2] - '0');
      break;
    default:
      return -1;
  }
  
  // Altitude
  if (comma_position[8] - comma_position[7] == 1) {
    gga->altitude = 0.0;
  } else {
    gga->altitude = 0.0;
    for (i=comma_position[7]+1; i<comma_position[8]; i++){
      gga->altitude *= 10;
      gga->altitude = sentence[comma_position[7] + 1 + i] - '0';
      ...
    }
  }
  
  ...
    
  return 0;
}
