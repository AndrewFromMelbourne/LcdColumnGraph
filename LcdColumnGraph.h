#ifndef LCD_COLUMN_GRAPH_H
#define LCD_COLUMN_GRAPH_H

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

#include <inttypes.h>

#if defined(ARDUINO) && ARDUINO >= 100
        #include "Arduino.h"
#else
        #include "WProgram.h"
#endif

#include "LiquidCrystal.h"



//-------------------------------------------------------------------------

class LcdColumnGraph 
{
public:

    LcdColumnGraph(
        LiquidCrystal& lcd,
        int32_t min,
        int32_t max,
        uint8_t column,
        uint8_t firstRow = 0,
        uint8_t lastRow = 1);

    void value(int32_t value)
    {
        unscaled(map(value, _min, _max, 0, _rows * 8));
    }

    void unscaled(uint8_t value);

    uint8_t getColumn() const { return _column; }
    void setColumn(uint8_t column) { _column = column; }

    int32_t getMin() const { return _min; }
    int32_t getMax() const { return _max; }

    void setMinMax(int32_t min, int32_t max) { _min = min; _max = max; }

private: 

    LiquidCrystal& _lcd;
    int32_t _min;
    int32_t _max;
    uint8_t _column;
    uint8_t _lastRow;
    uint8_t _rows;
    boolean _setup;

    void setup();
};

//-------------------------------------------------------------------------

#endif
