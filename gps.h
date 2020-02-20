
#ifndef __GPS_H
#define __GPS_H

struct GPSLocation { double latitude, longitude; };

static void gps_start();

static void gps_stop();

static GPSLocation gps_location();

#endif
