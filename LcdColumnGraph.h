//-------------------------------------------------------------------------
//
// The MIT License (MIT)
//
// Copyright (c) 2014 Andrew Duncan
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

#ifndef LCD_COLUMN_GRAPH_H
#define LCD_COLUMN_GRAPH_H

//-------------------------------------------------------------------------

#include <inttypes.h>

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

//-------------------------------------------------------------------------

template <typename LiquidCrystal_T>
class LcdColumnGraph 
{
public:

    LcdColumnGraph(
        LiquidCrystal_T& lcd,
        int32_t min,
        int32_t max,
        uint8_t column,
        uint8_t firstRow = 0,
        uint8_t lastRow = 1)
    :
        _lcd(lcd),
        _min(min),
        _max(max),
        _column(column),
        _lastRow(lastRow),
        _rows(lastRow - firstRow + 1),
        _setup(false)
    {
    }

    //---------------------------------------------------------------------

    void value(int32_t value)
    {
        unscaled(map(value, _min, _max, 0, _rows * 8));
    }

    //---------------------------------------------------------------------

    void unscaled(uint8_t value)
    {
        if (not _setup)
        {
            setup();
        }

        uint8_t letters = value / 8;
        uint8_t bar = value % 8;
        uint8_t letter = 0;


        for ( ; letter < letters ; ++letter)
        {
            _lcd.setCursor(_column, _lastRow - letter);
            _lcd.write((uint8_t)7);
        }

        if (bar)
        {
            _lcd.setCursor(_column, _lastRow - letter);
            _lcd.write(bar-1);
            ++letter;
        }

        for ( ; letter < _rows ; ++letter)
        {
            _lcd.setCursor(_column, _lastRow - letter);
            _lcd.print(" ");
        }
    }

    //---------------------------------------------------------------------

    uint8_t getColumn() const { return _column; }
    void setColumn(uint8_t column) { _column = column; }

    //---------------------------------------------------------------------

    int32_t getMin() const { return _min; }
    int32_t getMax() const { return _max; }

    //---------------------------------------------------------------------

    void setMinMax(int32_t min, int32_t max) { _min = min; _max = max; }

private: 

    LiquidCrystal_T& _lcd;
    int32_t _min;
    int32_t _max;
    uint8_t _column;
    uint8_t _lastRow;
    uint8_t _rows;
    boolean _setup;

    //---------------------------------------------------------------------

    void setup()
    {
        for (uint8_t letter = 0 ; letter < 8 ; ++letter)
        {
            byte pixels[8];

            for (uint8_t i = 0 ; i < 8 ; ++i)
            {
                if ((letter + 1) > (7 - i))
                {
                    pixels[i] = 0b11111;
                }
                else
                {
                    pixels[i] = 0;
                }
            }

            _lcd.createChar(letter, pixels);
        }

        _setup = true;
    }
};

#endif

