//-------------------------------------------------------------------------
//
// The MIT License (MIT)
//
// Copyright (c) 2013 Andrew Duncan
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to
// the following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
// CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
//-------------------------------------------------------------------------

#include <LcdColumnGraph.h>
#include <LiquidCrystal.h>

//-------------------------------------------------------------------------

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
LcdColumnGraph lcdColumnGraph(lcd, -8, 8, 0);

//-------------------------------------------------------------------------

void setup() 
{
    lcd.begin(16, 2);
}

//-------------------------------------------------------------------------

int32_t angle = 0;

//-------------------------------------------------------------------------

void loop()
{
    for (int8_t col = 0 ; col < 16 ; ++col)
    {
        int32_t phase = col * 24;
        lcdColumnGraph.setColumn(col);
        lcdColumnGraph.value(int(8.0 * sin((angle+phase) * DEG_TO_RAD)));
    }
    angle = (angle + 5) % 360;
    delay(30);
}

