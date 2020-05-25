#include <TTGO.h>

TTGOClass *ttgo;

char buf[128];

void setup()
{
    ttgo = TTGOClass::getWatch();
    ttgo->begin();
    ttgo->openBL();
    
    ttgo->eTFT->fillScreen(TFT_BLACK);

    ttgo->rtc->setDateTime(2020, 5, 25, 19, 36, 30);
}

void loop()
{
    ttgo->eTFT->setTextColor(random(0xFFFF));
    ttgo->eTFT->drawString("T-Watch Time",  50, 50, 4);

    ttgo->eTFT->setTextColor(TFT_YELLOW, TFT_BLACK);
    snprintf(buf, sizeof(buf), "%s", ttgo->rtc->formatDateTime());
    ttgo->eTFT->drawString(buf, 5, 118, 7);
    delay(1000);
}
