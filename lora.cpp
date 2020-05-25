#include "lora.h"
#include <TTGO.h>

static bool lora_enabled = false;
static bool lora_ever_enabled = false;
static S7XG_Class *s7xg;
static TTGOClass *ttgo = TTGOClass::getWatch();

void lora_start()
{
  lora_enabled = true;

  if ( ! lora_ever_enabled) {
    ttgo = TTGOClass::getWatch();
  
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
  
    Serial.println("Found s7xg module,Start lora module");
    lora_ever_enabled = true;
  }
}

void lora_stop()
{
  lora_enabled = false;
  ttgo->power->setPowerOutPut(AXP202_LDO3, AXP202_OFF);  //! Close s7xg chip power
  ttgo->power->setPowerOutPut(AXP202_LDO4, AXP202_OFF);  //! Close s7xg gps reset power
  s7xg = nullptr;
  lora_ever_enabled = false;
}
