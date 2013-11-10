#include "LcdColumnGraph.h"

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

LcdColumnGraph:: LcdColumnGraph(
	LiquidCrystal& lcd,
	int32_t min,
	int32_t max,
	uint8_t column,
	uint8_t firstRow,
	uint8_t lastRow)
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


//-------------------------------------------------------------------------

void
LcdColumnGraph:: setup()
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

//-------------------------------------------------------------------------

void
LcdColumnGraph:: unscaled(
	uint8_t value)
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
