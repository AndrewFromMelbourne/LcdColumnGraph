#include <LcdColumnGraph.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
LcdColumnGraph lcdColumnGraph(lcd, -8, 8, 0);

void setup() 
{
    lcd.begin(16, 2);
}

int32_t angle = 0;

void loop()
{
    for (int8_t col = 0 ; col < 16 ; ++col)
    {
        int32_t phase = col * 24;
        lcdColumnGraph.setColumn(col);
        lcdColumnGraph.value(int(8.0 * sin((angle+phase) * 3.141592654 / 180.0)));
    }
    angle = (angle + 5) % 360;
    delay(30);
}

