#include <M5Stack.h>

void renderIcon(uint16_t symbol);

struct Indicator
{
    boolean active;
    boolean rec;
    boolean play;
    boolean check;
    boolean solo;
    boolean selected;
};

void renderIndicator(uint8_t pos, Indicator indicator);

void activateTrack(uint8_t track);