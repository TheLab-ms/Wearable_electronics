/*
 * demo.h
 *
 *  Created on: Feb 3, 2016
 *      Author: Bill
 */

#ifndef DEMO_H_
#define DEMO_H_

#define	DEMO

//*********** EXTERNAL VARIABLES ***********************************************
extern const unsigned char font_basic[ ][8];

#define MAX_SCAN    10

unsigned int	num_cycles;
unsigned int	scan;
unsigned int	offset;

const unsigned char	*current_char;

// ***
// Below spells out T h e L A B . m s (space) in unicode HEX
// ***
const unsigned char charstodisplay[ ] = " TheLAB.ms\0";

void init_demo(void)
{
    num_cycles = MAX_SCAN;
    scan = 0;
    current_char = charstodisplay;
}

void blt_char(unsigned char ch, int origin)
{
	unsigned int	i;
	unsigned int	row;
	unsigned int	col;
	unsigned int	columns;
	unsigned char	*display;
	unsigned char	font_row;

	const unsigned char	*font;

	if (origin < -7 || origin > 7)
		return;

	font = font_basic[ch];
	display = display_buffer;
	columns = 8;

	for (row = 0; row < 8; row++)
		{
		font_row = *font++;

		if (origin < 0)
			{
			// Glyph is offset to the left, lose that many columns
			for (i = 0; i < abs(origin); i++)
				font_row = font_row >> 1;

			columns = 8 + origin;
			}
		if (origin > 0)
			{
			// Glyph is offset to the right, skip that many columns
			display = display + 3 * origin;
			columns = 8 - origin;
			}

		for (col = 0; col < columns; col++)
			{
			if (font_row & 1)
				{
				*display++ = MAX_DELAY;
				*display++ = MAX_DELAY;
				*display++ = MAX_DELAY;
				}
			else
				display = display + 3;

			font_row = font_row >> 1;
			}

		if (origin < 0)
			// Glyph is offset to the left, leave that many columns on the right
			display = display + 3 * abs(origin);
		}
}

void step_demo(void)
{
	unsigned int	i;

    // Clear video buffer
    for (i = 0; i < 192; i++)
        display_buffer[i] = 0;

    blt_char(*current_char, -offset);
    if (offset > 0)
    	// Do part of the next character
    	blt_char(*(current_char + 1), 8 - offset);

    if (offset < 7)
    	offset++;
    else
    	{
    	// Next character
    	offset = 0;
    	if (*current_char == 0)
    		current_char = charstodisplay;
    	else
    		current_char++;
    	}
}

#endif /* DEMO_H_ */
