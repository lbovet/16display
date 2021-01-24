#include "indicator.h"
#include "colors.h"

Indicator indicators[16];
uint8_t current = 0;

void activateTrack(uint8_t track)
{
    uint8_t group = track / 4;
    if (group != current / 4)
    {
        renderIcon(group + 65);
    }
    uint8_t pos = track % 4;
    if (pos != current % 4)
    {
        indicators[current].active = false;
        renderIndicator(current % 4, indicators[current]);
        indicators[track].active = true;
        renderIndicator(pos, indicators[track]);
    }
    current = track;
}

void renderIcon(uint16_t symbol)
{
    M5.Lcd.fillRect(0, 0, 64, 64, BACKGROUND);
    M5.Lcd.setTextColor(ACCENT);
    M5.Lcd.setTextSize(5);
    M5.Lcd.drawChar(symbol, 19, 12);
}

void renderIndicator(uint8_t pos, Indicator indicator)
{
    uint32_t x = pos * 64 + 65;
    const uint32_t h = 58;
    const uint32_t w = 62;
    uint16_t tcolor = indicator.active ? BACKGROUND : SECONDARY;
    uint16_t bgcolor = ACCENT;
    uint16_t lcolor = indicator.active ? HIGHLIGHT : NORMAL;

    M5.Lcd.fillRect(x, 0, w, h, BACKGROUND);

    if (indicator.solo)
    {
        bgcolor = NORMAL;
    }

    if (indicator.active)
    {
        if (indicator.rec)
        {
            M5.Lcd.fillCircle(x + w / 2, h / 2, h / 2 - 4, bgcolor);
        }
        else
        {
            M5.Lcd.fillRoundRect(x, 0, w, h, 4, bgcolor);
        }
        lcolor = HIGHLIGHT;
    }

    if (indicator.play)
    {
        tcolor = HIGHLIGHT;
    }

    M5.Lcd.setTextColor(tcolor);
    M5.Lcd.setTextSize(5);
    M5.Lcd.drawChar(char(pos + 49), x + 19, 12);

    if (indicator.check)
    {
        M5.Lcd.drawLine(x + 8, h - 8, x + w - 8, 8, lcolor);
        M5.Lcd.drawLine(x + 8, 8, x + w - 8, h - 8, lcolor);
    }

    if (indicator.selected)
    {
        M5.Lcd.drawRoundRect(x + 6, 6, w - 12, h - 12, 4, lcolor);
    }
}