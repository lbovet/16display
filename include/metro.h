#include <M5Stack.h>
#include <colors.h>

void renderBeat(uint16_t enabledBars, uint8_t tick);

void metroLine(uint16_t enabledBars, uint8_t activeGroup);

void square(uint8_t pos, uint8_t size, uint16_t color, boolean filled);

uint32_t posToX(uint8_t pos);