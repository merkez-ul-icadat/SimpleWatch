#ifndef __GPS_H
#define __GPS_H

struct GPSLocation { double latitude, longitude; };

void gps_start();

void gps_stop();

GPSLocation gps_location();

#endif
