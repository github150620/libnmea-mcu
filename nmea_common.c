

int nmea_parse_latitude(char *s, int len, double *latitude) {
  if (len <= 0 || len < 4) return -1;
  
  *latitude = 0.0;
  *latitude += (s[0] - '0') * 10;
  *latitude += (s[1] - '0') * 1;
  *latitude += (s[2] - '0') / 6.0;
  *latitude += (s[3] - '0') / 60.0;

  if (len >= 5 && s[4]!='.') return -1;

  if (len >= 6)  *latitude += (s[5] - '0') / 600.0;
  if (len >= 7)  *latitude += (s[6] - '0') / 6000.0;
  if (len >= 8)  *latitude += (s[7] - '0') / 60000.0;
  if (len >= 9)  *latitude += (s[8] - '0') / 600000.0;
  if (len >= 10) *latitude += (s[9] - '0') / 6000000.0;  

  return 0;
}

int nmea_parse_longitude(char *s, int len, double *longitude) {
  if (len <= 0 || len < 5) return -1;
  
  *longitude = 0.0;
  *longitude += (s[0] - '0') * 100;
  *longitude += (s[1] - '0') * 10;
  *longitude += (s[2] - '0') * 1;
  *longitude += (s[3] - '0') / 6.0;
  *longitude += (s[4] - '0') / 60.0;

  if (len >= 6 && s[5]!='.') return -1;

  if (len >= 7)  *longitude += (s[6]  - '0') / 600.0;
  if (len >= 8)  *longitude += (s[7]  - '0') / 6000.0;
  if (len >= 9)  *longitude += (s[8]  - '0') / 60000.0;
  if (len >= 10) *longitude += (s[9]  - '0') / 600000.0;
  if (len >= 11) *longitude += (s[10] - '0') / 6000000.0;  

  return 0;
}
