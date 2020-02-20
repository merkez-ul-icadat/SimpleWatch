#include "gps.h"
#include <TTGO.h>

bool gps_enabled = false;
S7XG_Class *s7xg;
TTGOClass *ttgo = TTGOClass::getWatch();
TinyGPSPlus *gps;
char buff[256];

static void gps_start()
{
  gps_enabled = true;
  
  ttgo = TTGOClass::getWatch();
  ttgo->begin();
  ttgo->openBL();

  //! Open s7xg power
  ttgo->enableLDO4();
  ttgo->enableLDO3();

  ttgo->s7xg_begin();
  s7xg = ttgo->s7xg;

  int len = 0;
  int retry = 0;
  do {
    len = s7xg->getHardWareModel().length();
    if (len == 0 && retry++ == 5) {
      s7xg->reset();
      retry = 0;
      Serial.println("Reset s7xg chip");
    }
    if (len == 0)
      delay(1000);
  } while (len == 0);

  Serial.println("Found s7xg module,Start gps module");

  s7xg->gpsReset();
  s7xg->gpsSetLevelShift(true);
  s7xg->gpsSetStart();
  s7xg->gpsSetSystem(0);
  s7xg->gpsSetPositioningCycle(1000);
  s7xg->gpsSetPortUplink(20);
  s7xg->gpsSetFormatUplink(1);
  s7xg->gpsSetMode(1);
  
  ttgo->gps_begin();
}

static GPSLocation gps_location()
{
  GPS_Class gps =  s7xg->gpsGetData();
  GPSLocation location;
  
  if (gps.isVaild()) {
    // sprintf(buff, "Location: lat:%.02f lng:%.02f", gps.lat(), gps.lng());
    location.latitude = gps.lat();
    location.longitude = gps.lng();
  }

  return location;
}

static void gps_stop()
{
  gps_enabled = false;
}
