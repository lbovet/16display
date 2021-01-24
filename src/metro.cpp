#include "metro.h"

void metroLine(uint16_t enabledBars, uint8_t activeGroup)
{
    for (int i = 0; i < 16; i++)
    {
        square(i, 0, i / 4 == activeGroup ? NORMAL : SECONDARY, (1 << i) & enabledBars);
    }
}

void renderBeat(uint16_t enabledBars, uint8_t tick)
{
    uint8_t pos = tick / 8;
    uint8_t eighth = tick % 8;
    uint8_t beat = eighth / 2 + 1;
    boolean even = tick % 2;
    if(eighth == 0) {
        metroLine(enabledBars, tick / 32);
    }
    square(pos, 0, BACKGROUND, true);
    square(pos, beat, even ? ACCENT : HIGHLIGHT, true);
}

void square(uint8_t pos, uint8_t beat, uint16_t color, boolean filled)
{
    const uint32_t fw = 16;
    const uint32_t fh = 14;
    const uint32_t w = beat == 0 ? fw : 9;
    const uint32_t h = beat == 0 ? fh : 8;
    const uint32_t y = 238 - fh;
    const uint32_t xoffset = (beat == 2 || beat == 3) ? 7 : 0;
    const uint32_t yoffset = (beat == 3 || beat == 4) ? 6 : 0;

    if (beat != 0)
    {
        M5.Lcd.fillRect(posToX(pos), y, fw, fh, BACKGROUND);
    }

    if (filled)
    {
        M5.Lcd.fillRoundRect(posToX(pos) + xoffset, y + yoffset, w, h, 2, color);
    }
    else
    {
        M5.Lcd.fillRoundRect(posToX(pos) + xoffset, y + yoffset, w, h, 2, BACKGROUND);
        M5.Lcd.drawRoundRect(posToX(pos) + xoffset, y + yoffset, w, h, 2, color);
    }
}

uint32_t posToX(uint8_t pos)
{
    uint32_t x = 2 + pos * 20;
    return x;
}