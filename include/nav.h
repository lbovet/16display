#include <M5Stack.h>

extern char text[5][30];
extern int selected;

void renderNav();
void selectText(int pos);
void clearText();
