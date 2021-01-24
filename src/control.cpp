#include "control.h"
#include "colors.h"

char module[30];
char page[30];
Control controls[4];
int lastControl = 5;
uint8_t ctrlEvents = 0;

void title(char *module, char *page)
{
    const uint32_t h = 156;
    const uint32_t y = 66;
    M5.Lcd.fillRect(0, y, 320, h, BACKGROUND);

    M5.Lcd.setTextSize(2);

    M5.Lcd.setTextColor(HIGHLIGHT);
    M5.Lcd.setTextDatum(TL_DATUM);
    M5.Lcd.drawString(module, 4, y+2);

    M5.Lcd.setTextColor(NORMAL);
    M5.Lcd.setTextDatum(TR_DATUM);
    M5.Lcd.drawString(page, 319, y+2);

    for (int i = 0; i < 4; i++)
    {
        controls[i].desc[0] = 0;
    }

    lastControl = 5;
    ctrlEvents = 0;
}

void renderControl(uint8_t pos, Control control, boolean active)
{
    const uint32_t h = 34;
    const uint32_t y = 94 + pos * h;
    const uint32_t ybar = y + 21;
    const uint32_t thickness = active ? 30 : 3;

    if (controls[pos].desc[0] == 0)
    {
        return;
    }

    M5.Lcd.fillRect(active ? 319 * control.ctrl - 3 : 0, ybar - 30, 319, 30, BACKGROUND);

    if (control.ctrl >=0)
    {
        M5.Lcd.fillRoundRect(0, ybar - thickness, 319 * control.ctrl, thickness, active ? 3 : 1, active ? ACCENT : SECONDARY);
    }
    M5.Lcd.setTextSize(2);

    M5.Lcd.setTextColor(active ? WHITE : NORMAL);
    M5.Lcd.setTextDatum(TL_DATUM);
    M5.Lcd.drawString(control.desc, 4, y);

    M5.Lcd.setTextColor(active ? WHITE : ACCENT);
    M5.Lcd.setTextDatum(TR_DATUM);
    M5.Lcd.drawString(control.value, 319, y);
}