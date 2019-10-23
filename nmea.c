#include "nmea.h"
#include <stdint.h>
#include <string.h>

/* Example:
 *   $GPRMC,073601.00,A,2930.74875,N,10634.26655,E,2.592,181.57,231019,,,D*65\r\n
 */
int nmea_parse_rmc(char *sentence, nmea_gprmc_t *rmc) {
  char *p;
  int i;
  int j = 0;
  
  uint8_t comma_position[12];
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

  // There must be 12 commas in a RMC sentence.
  if (j != 12) {
    return -1;
  }
  
  if (strncmp(sentence, "$GPRMC", comma_position[0] - 0) != 0) {
    return -1;
  }
  
  // time
  if (comma_position[1] - comma_position[0] == 1) {
    rmc->time[0] = '\0';
  } else if (comma_position[1] - comma_position[0] >= 7) {
    memcpy(rmc->time, &sentence[comma_position[0]+1], 6);
  } else {
    return -1;
  }
  
  // Status
  if (comma_position[2] - comma_position[1] == 1) {
    rmc->status = 'U';
  } else if (comma_position[2] - comma_position[1] == 2) {
    rmc->status = sentence[comma_position[1]+1];
  } else {
    return -1;
  }
  
  // Latitude
  if (comma_position[3] - comma_position[2] == 1) {
    rmc->latitude = 0.0;
  } else if (comma_position[3] - comma_position[2] >= 9) {
    p = &sentence[comma_position[2]+1];
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

  if (comma_position[4] - comma_position[3] == 1) {
    rmc->latitude = 0.0;
  } else if (comma_position[4] - comma_position[3] == 2) {
    switch (sentence[comma_position[3]+1])
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
  if (comma_position[5] - comma_position[4] == 1) {
    rmc->longitude = 0.0;
  } else if (comma_position[5] - comma_position[4] >= 10) {
    p = &sentence[comma_position[2]+1];
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

  if (comma_position[6] - comma_position[5] == 1) {
    rmc->longitude = 0.0;
  } else if (comma_position[6] - comma_position[5] == 2) {
    switch (sentence[comma_position[5]+1])
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

  // speed
  if (comma_position[7] - comma_position[6] == 1) {
    rmc->speed = 0.0;
  } else if (comma_position[7] - comma_position[6] >= 5) {
    p = &sentence[comma_position[6]+1];
    rmc->speed = 0.0;
    for (i=0; i < comma_position[7] - comma_position[6] - 1; i++) {
      if (p[i] == '.') break;
      rmc->speed = rmc->speed * 10.0 + (p[i] - '0');
    }
    if (p[i+1] != ',') {
      rmc->speed += (p[i+1] - '0') * 0.1;
      if (p[i+2] != ',') {
        rmc->speed += (p[i+2] - '0') * 0.01;
        if (p[i+3] != ',') {
          rmc->speed += (p[i+3] - '0') * 0.001;
        }
      }
    }
  } else {
    return -1;
  }
  // heading

  return 0;
}
