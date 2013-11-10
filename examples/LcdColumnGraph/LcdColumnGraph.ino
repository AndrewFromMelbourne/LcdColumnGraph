#include <LcdColumnGraph.h>
#include <LiquidCrystal.h>

//-------------------------------------------------------------------------
// Copyright (C) 2012 Andrew Duncan.
//
// This software may be distributed and modified under the terms of the GNU
// General Public License version 2 (GPL2) as published by the Free Software
// Foundation and appearing in the file GPL2.TXT included in the packaging
// of this file. Please note that GPL2 Section 2[b] requires that all works
// based on this software must also be made publicly available under the
// terms of the GPL2 ("Copyleft").
//
//-------------------------------------------------------------------------

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
        lcdColumnGraph.value(int(8.0 * sin((angle+phase) * DEG_TO_RAD)));
    }
    angle = (angle + 5) % 360;
    delay(30);
}

