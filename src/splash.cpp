#include "splash.h"
#include "indicator.h"
#include "colors.h"
#include "metro.h"

void header()
{
    renderIcon('A');
    renderIndicator(0, Indicator({.active = true}));
    renderIndicator(1, Indicator());
    renderIndicator(2, Indicator());
    renderIndicator(3, Indicator());
}

void splash(boolean on)
{
    M5.Lcd.clearDisplay();

    uint32_t yoff = -20;

    if (on)
    {
        yoff = 0;
        metroLine(13107, -1);
        header();
    }

    M5.Lcd.setTextColor(NORMAL);
    M5.Lcd.setTextSize(18);
    M5.Lcd.setTextDatum(TL_DATUM);
    M5.Lcd.drawString("16", 48, 100 + yoff);
    M5.Lcd.drawFastHLine(135, 100 + yoff, 320 - 120, NORMAL);
    M5.Lcd.drawFastHLine(135, 106 + yoff, 320 - 120, NORMAL);

    M5.Lcd.setTextColor(ACCENT);
    M5.Lcd.setTextSize(30);
    M5.Lcd.setTextDatum(BR_DATUM);
    M5.Lcd.drawString("BOX", 272, 180 + yoff);
    M5.Lcd.drawFastHLine(0, 166 + yoff, 134, ACCENT);
    M5.Lcd.drawFastHLine(0, 172 + yoff, 134, ACCENT);
}