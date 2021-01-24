#include "control.h"
#include "colors.h"
#include "nav.h"

char text[5][30];
int selected = 0;

void renderText(int pos)
{
    const uint32_t h = 30;
    const uint32_t y = 76 + pos * h;
    const uint32_t ybar = y + 21;
    const uint32_t thickness = 30;
    boolean active = (pos == selected);

    if (active)
    {
        M5.Lcd.fillRoundRect(0, ybar - thickness, 319, thickness, 3, ACCENT);
    }
    else
    {
        M5.Lcd.fillRect(0, ybar - thickness, 319, thickness, BACKGROUND);
    }

    M5.Lcd.setTextSize(2);

    M5.Lcd.setTextColor(active ? WHITE : NORMAL);
    M5.Lcd.setTextDatum(TL_DATUM);
    M5.Lcd.drawString(text[pos], 4, y);
}

void renderNav()
{
    for (int i = 0; i < 5; i++)
    {
        renderText(i);
    }
}

void selectText(int pos)
{
    if (pos != selected)
    {
        selected = pos;
        renderText(pos);
    }
}

void clearText()
{
    const uint32_t h = 156;
    const uint32_t y = 68;
    M5.Lcd.fillRect(0, y, 320, h, BACKGROUND);
}
