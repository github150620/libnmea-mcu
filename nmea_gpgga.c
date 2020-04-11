#include "nmea.h"
#include "nmea_common.h"

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
    nmea_parse_latitude(
      &sentence[comma_position[1]+1],
      comma_position[2] - comma_position[1] - 1,
      &gga->latitude
    );
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
    nmea_parse_longitude(
      &sentence[comma_position[3]+1],
      comma_position[4] - comma_position[3] - 1,
      &gga->longitude
    );
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
    case 1:
      gga->NoSBT = 0;
      break;
    case 3:
      gga->NoSBT = sentence[comma_position[6]+1] - '0';
      gga->NoSBT = gga->NoSBT * 10 + (sentence[comma_position[6]+2] - '0');
      break;
    default:
      return -1;
  }
  
  // Horizontal dilution of position
  if (comma_position[8] - comma_position[7] == 1) {
      gga->HDoP = 0.0;
  } else {
      nmea_parse_double(
        &sentence[comma_position[7]+1],
        comma_position[8] - comma_position[7] - 1,
        &gga->HDoP
      );
  }

  // Altitude
  if (comma_position[9] - comma_position[8] == 1) {
    gga->altitude = 0.0;
  } else {
    gga->altitude = 0.0;
    nmea_parse_double(
      &sentence[comma_position[8]+1], 
      comma_position[9] - comma_position[8] - 1,
      &gga->altitude
    );
  }

  switch (comma_position[10] - comma_position[9]) {
    case 1:
      gga->altitude = 0.0;
      break;
    case 2:
      switch (sentence[comma_position[9]+1]) {
        case 'M':
          gga->altitude *= 1.0;
          break;
        case 'K':
          gga->altitude *= 1000.0;
          break;
        default:
          return -1;
      }
      break;
    default:
      return -1;
  }

  if (comma_position[11] - comma_position[10] == 1) {
    gga->HoG = 0.0;
  } else {
    gga->HoG = 0.0;
    nmea_parse_double(
      &sentence[comma_position[10]+1], 
      comma_position[11] - comma_position[10] - 1,
      &gga->HoG
    );
  }

  switch (comma_position[12] - comma_position[11]) {
    case 1:
      gga->HoG = 0.0;
      break;
    case 2:
      switch (sentence[comma_position[11]+1]) {
        case 'M':
          gga->HoG *= 1.0;
          break;
        case 'K':
          gga->HoG *= 1000.0;
          break;
        default:
          return -1;
      }
      break;
    default:
      return -1;
  }

  return 0;
}
