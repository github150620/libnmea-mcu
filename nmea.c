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
      asterisk_postion = i;
    }
  }

  // There must be 12 commas in a RMC sentence.
  if (j != 12) {
    return -1;
  }
  
  if (strncmp(sentence, "$GPRMC", comma_postion[0] - 0) != 0) {
    return -1;
  }
  
  // time
  if (comma_postion[1] - comma_postion[0] == 1) {
    rmc->time[0] = '\0';
  } else if (comma_postion[1] - comma_postion[0] >= 7) {
    memcpy(rmc->time, &sentence[comma_postion[0]+1], 6);
  } else {
    return -1;
  }
  
  // Status
  if (comma_postion[2] - comma_postion[1] == 1) {
    rmc->status = 'U';
  } else if (comma_postion[2] - comma_postion[1] == 2) {
    rmc->status = sentence[comma_postion[1]+1];
  } else {
    return -1;
  }
  
  // Latitude
  if (comma_postion[3] - comma_postion[2] == 1) {
    rmc->latitude = 0.0;
  } else if (comma_postion[3] - comma_postion[2] >= 8) {
    p = &sentence[comma_postion[2]+1];
    rmc->latitude = 0.0;
    rmc->latitude += (p[0] - '0') * 10;
    rmc->latitude += (p[1] - '0') * 1;
    rmc->latitude += (p[2] - '0') / 6.0;
    rmc->latitude += (p[3] - '0') / 60.0;
    if (p[4] != '.') return -1;
    rmc->latitude += (p[5] - '0') / 600.0;
    rmc->latitude += (p[6] - '0') / 6000.0;
    rmc->latitude += (p[7] - '0') / 6000.0;
  } else {
    return -1;
  }
  return 0;
}
