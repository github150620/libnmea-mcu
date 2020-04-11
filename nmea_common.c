

int nmea_parse_latitude(char *s, int len, double *latitude) {
  double lat = 0.0;
  if (len <= 0 || len < 4) return -1;
  
  lat += (s[0] - '0') * 10;
  lat += (s[1] - '0') * 1;
  lat += (s[2] - '0') / 6.0;
  lat += (s[3] - '0') / 60.0;

  if (len >= 5 && s[4]!='.') return -1;

  if (len >= 6)  lat += (s[5] - '0') / 600.0;
  if (len >= 7)  lat += (s[6] - '0') / 6000.0;
  if (len >= 8)  lat += (s[7] - '0') / 60000.0;
  if (len >= 9)  lat += (s[8] - '0') / 600000.0;
  if (len >= 10) lat += (s[9] - '0') / 6000000.0;  

  *latitude = lat;
  return 0;
}

int nmea_parse_longitude(char *s, int len, double *longitude) {
  double lng = 0.0;

  if (len <= 0 || len < 5) return -1;
  
  lng += (s[0] - '0') * 100;
  lng += (s[1] - '0') * 10;
  lng += (s[2] - '0') * 1;
  lng += (s[3] - '0') / 6.0;
  lng += (s[4] - '0') / 60.0;

  if (len >= 6 && s[5]!='.') return -1;

  if (len >= 7)  lng += (s[6]  - '0') / 600.0;
  if (len >= 8)  lng += (s[7]  - '0') / 6000.0;
  if (len >= 9)  lng += (s[8]  - '0') / 60000.0;
  if (len >= 10) lng += (s[9]  - '0') / 600000.0;
  if (len >= 11) lng += (s[10] - '0') / 6000000.0;  

  *longitude = lng;
  return 0;
}

int nmea_parse_double(char *s, int len, double *d) {
  double d1 = 0.0;
  double exp = 1.0;
  int i;
  int point = 0;

  if (len <=0 ) return -1;

  for (i=0;i<len;i++) {
    if (s[i] == '.') {
        point = 1;
        continue;
    }
    d1 = d1 * 10 + (s[i] - '0');
    if (point == 1) {
        exp *= 10;
    }
  }

  *d = d1 / exp;
  return 0;
}
