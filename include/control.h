#include <M5Stack.h>

extern char module[];
extern char page[];

struct Control
{
    char desc[30];
    char value[30];
    float ctrl;
};

extern Control controls[];

extern int lastControl;
extern uint8_t ctrlEvents;

void title(char *module, char *page);

void renderControl(uint8_t pos, Control control, boolean active);