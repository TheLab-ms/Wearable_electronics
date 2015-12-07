/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using MPLAB® Code Configurator

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB® Code Configurator - v2.25.2
        Device            :  PIC16F1947
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC8 v1.34
        MPLAB             :  MPLAB X v2.35 or v3.00
 */

/*
Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 */

#include "mcc_generated_files/mcc.h"

//*********** EXTERNAL VARIABLES ***********************************************
extern const unsigned char font_basic[ ][8];

//*********** Map rows to hardware *********************************************
#define ROW0_ON     RB1_ROW0_SetHigh
#define ROW0_OFF    RB1_ROW0_SetLow

#define ROW1_ON     RB2_ROW1_SetHigh
#define ROW1_OFF    RB2_ROW1_SetLow

#define ROW2_ON     RB3_ROW2_SetHigh
#define ROW2_OFF    RB3_ROW2_SetLow

#define ROW3_ON     RB4_ROW3_SetHigh
#define ROW3_OFF    RB4_ROW3_SetLow

#define ROW4_ON     RB5_ROW4_SetHigh
#define ROW4_OFF    RB5_ROW4_SetLow

#define ROW5_ON     RB6_ROW5_SetHigh
#define ROW5_OFF    RB6_ROW5_SetLow

#define ROW6_ON     RB7_ROW6_SetHigh
#define ROW6_OFF    RB7_ROW6_SetLow

#define ROW7_ON     RC1_ROW7_SetHigh
#define ROW7_OFF    RC1_ROW7_SetLow

//*********** Map columns to hardware ******************************************
#define COL0R_ON    RD0_C1R_SetLow
#define COL0R_OFF   RD0_C1R_SetHigh
#define COL0G_ON    RD1_C2G_SetLow
#define COL0G_OFF   RD1_C2G_SetHigh
#define COL0B_ON    RD2_C3B_SetLow
#define COL0B_OFF   RD2_C3B_SetHigh

#define COL1R_ON    RD3_C4R_SetLow
#define COL1R_OFF   RD3_C4R_SetHigh
#define COL1G_ON    RD4_C5G_SetLow
#define COL1G_OFF   RD4_C5G_SetHigh
#define COL1B_ON    RD5_C6B_SetLow
#define COL1B_OFF   RD5_C6B_SetHigh

#define COL2R_ON    RD6_C7R_SetLow
#define COL2R_OFF   RD6_C7R_SetHigh
#define COL2G_ON    RD7_C8G_SetLow
#define COL2G_OFF   RD7_C8G_SetHigh
#define COL2B_ON    RE0_C9B_SetLow
#define COL2B_OFF   RE0_C9B_SetHigh

#define COL3R_ON    RE1_C10R_SetLow
#define COL3R_OFF   RE1_C10R_SetHigh
#define COL3G_ON    RE2_C11G_SetLow
#define COL3G_OFF   RE2_C11G_SetHigh
#define COL3B_ON    RE3_C12B_SetLow
#define COL3B_OFF   RE3_C12B_SetHigh

#define COL4R_ON    RE4_C13R_SetLow
#define COL4R_OFF   RE4_C13R_SetHigh
#define COL4G_ON    RE5_C14G_SetLow
#define COL4G_OFF   RE5_C14G_SetHigh
#define COL4B_ON    RE6_C15B_SetLow
#define COL4B_OFF   RE6_C15B_SetHigh

#define COL5R_ON    RE7_C16R_SetLow
#define COL5R_OFF   RE7_C16R_SetHigh
#define COL5G_ON    RF0_C17G_SetLow
#define COL5G_OFF   RF0_C17G_SetHigh
#define COL5B_ON    RF1_C18B_SetLow
#define COL5B_OFF   RF1_C18B_SetHigh

#define COL6R_ON    RF2_C19R_SetLow
#define COL6R_OFF   RF2_C19R_SetHigh
#define COL6G_ON    RF3_C20G_SetLow
#define COL6G_OFF   RF3_C20G_SetHigh
#define COL6B_ON    RF4_C21B_SetLow
#define COL6B_OFF   RF4_C21B_SetHigh

#define COL7R_ON    RF5_C22R_SetLow
#define COL7R_OFF   RF5_C22R_SetHigh
#define COL7G_ON    RF6_C23G_SetLow
#define COL7G_OFF   RF6_C23G_SetHigh
#define COL7B_ON    RF7_C24B_SetLow
#define COL7B_OFF   RF7_C24B_SetHigh

//*********** Global Variables *************************************************
unsigned char current_column_position;
unsigned char delay_ptr;
unsigned char delay_time[192];
unsigned char current_red_level;
unsigned char current_green_level;
unsigned char current_blue_level;
unsigned int LED_R[64];
unsigned int LED_G[64];
unsigned int LED_B[64];

//*********** Prototypes *******************************************************
void strobe_all();
void big_switch_rows(unsigned char pos);
void big_switch_columns();
void all_off();
void all_on(unsigned char ao);
void test_pattern();
void usec_delay(unsigned int usec);
void my_delay(unsigned char dly);
void init_font_LED_data(unsigned char ctxt, unsigned char cnext, unsigned int offset);
void Display_LED_data();


//******************************************************************************
void main(void) 
{
    unsigned char x, y;
    unsigned int offset;
    unsigned char charnext;
    
    SYSTEM_Initialize();// initialize the device

    //INTERRUPT_GlobalInterruptEnable();// Enable
    //INTERRUPT_PeripheralInterruptEnable();// Enable
    //INTERRUPT_GlobalInterruptDisable();// Disable
    //INTERRUPT_PeripheralInterruptDisable();// Disable

    // ***
    // these color levels will be set for every ASCII character
    // this is also the delay value for each color
    // total of all three values should not exceed 50 or flicker will occur
	// ***
    current_red_level   = 10; //red
    current_green_level = 10; //green
	current_blue_level  = 10; //blue
    
    // ***
    // Determine if scrolling text or char by char display
    unsigned int scroll = 1;
    
    // ***
    // Below spells out T h e L A B . m s (space) in unicode HEX
    // ***
    const unsigned char charstodisplay[ ] = {0x54, 0x68, 0x65, 0x4C, 0x41, 0x42, 0x2E, 0x6D, 0x73, 0x00};

    while (1)
    {
        //ALL OFF
        all_off();
        
        if (scroll == 0)
        {
            //Loop through each char
            for (x=0; x<(sizeof(charstodisplay)); x++)
            {
                init_font_LED_data(charstodisplay[x], 0x00, 0);
                //Loop same char a number of times so it stays on screen
                for (y=0; y<100; y++)
                {
                    Display_LED_data();
                }   
            } 
        }
        else
        {
            //
            for (x=0; x<(sizeof(charstodisplay)); x++)
            {
                for (offset=0; offset<8; offset++)
                {
                    if( (x+1) > (sizeof(charstodisplay)-1) ) { charnext = charstodisplay[0]; } else { charnext = charstodisplay[x+1]; }
                    init_font_LED_data(charstodisplay[x], charnext, offset);
                    //Loop same char a number of times so it stays on screen
                    for (y=0; y<12; y++)
                    {
                        Display_LED_data();
                    }   
                }
            }
        }
    }

    
}

//******************************************************************************
void init_font_LED_data(unsigned char ctxt, unsigned char cnext, unsigned int offset)
{
	unsigned int h, i, j;
	const unsigned char mask = 1;
	volatile unsigned int tempbit = 0;
    volatile unsigned int dvalue = 0;

	h =0;

	// Loops Through Each Byte in both the ctxt and cnext arrays
	for( j = 0; j < 8; j++)
	{

		// Loops Through Each Bit in each Byte in data array
		for ( i = 0; i < 8; i++ )
		{
			if ( i >= offset ) {  // Skips bits of offset value to be filled in with cnext array for scrolling text
				tempbit   = (font_basic[ctxt][j] & ( mask << i ) ) != 0;
                //LED_R[h] = tempbit * (((257-ctxt)+current_red_level)/10);
                //LED_G[h] = tempbit * (((257-ctxt)+current_green_level)/10);
                //LED_B[h] = tempbit * (((257-ctxt)+current_blue_level)/10);
                dvalue = ((400-ctxt));
                LED_R[h] = tempbit * (((dvalue)*current_red_level)/400);
                LED_G[h] = tempbit * (((dvalue)*current_green_level)/400);
                LED_B[h] = tempbit * (((dvalue)*current_blue_level)/400);
				//LED_R[h] = tempbit * (current_red_level);
                //LED_G[h] = tempbit * (current_green_level);
                //LED_B[h] = tempbit * (current_blue_level);
                h++;
			}
		}

		if (offset >= 1) {  // Only do this second loop if needed
			// Loops Through Each Bit in each Byte in datanext array
			for ( i = 0; i < 8; i++ )
			{
				if ( offset > i ) {  // Fills in the bits skipped in the first byte with bits from the next byte
					tempbit   = (font_basic[cnext][j] & ( mask << i ) ) != 0;
					//LED_R[h] = tempbit * (((257-cnext)+current_red_level)/10);
                    //LED_G[h] = tempbit * (((257-cnext)+current_green_level)/10);
                    //LED_B[h] = tempbit * (((257-cnext)+current_blue_level)/10);
                    dvalue = ((400-cnext));
                    LED_R[h] = tempbit * (((dvalue)*current_red_level)/400);
                    LED_G[h] = tempbit * (((dvalue)*current_green_level)/400);
                    LED_B[h] = tempbit * (((dvalue)*current_blue_level)/400);
                    //LED_R[h] = tempbit * (current_red_level);
                    //LED_G[h] = tempbit * (current_green_level);
                    //LED_B[h] = tempbit * (current_blue_level);
					h++;
				}
			}
		}

	}

}

//******************************************************************************
void Display_LED_data()
{
    unsigned int i;
    
    //ALL OFF
    //all_off();

    //Loop Through All 64 LEDs to set values
    for ( i = 0; i < 64; i++)
    {
        if (LED_R[i] > 0)
        {
            //ROW ON
            if (i < 8) { ROW0_ON(); }
            if ((i >= 8) && (i < 16)) { ROW1_ON(); }
            if ((i >= 16) && (i < 24)) { ROW2_ON(); }
            if ((i >= 24) && (i < 32)) { ROW3_ON(); }
            if ((i >= 32) && (i < 40)) { ROW4_ON(); }
            if ((i >= 40) && (i < 48)) { ROW5_ON(); }
            if ((i >= 48) && (i < 56)) { ROW6_ON(); }
            if ((i >= 56) && (i < 64)) { ROW7_ON(); }
            //COL ON
            if ((i == 0)||(i == 8)||(i == 16)||(i == 24)||(i == 32)||(i == 40)||(i == 48)||(i == 56)) { COL0R_ON(); }
            if ((i == 1)||(i == 9)||(i == 17)||(i == 25)||(i == 33)||(i == 41)||(i == 49)||(i == 57)) { COL1R_ON(); }
            if ((i == 2)||(i == 10)||(i == 18)||(i == 26)||(i == 34)||(i == 42)||(i == 50)||(i == 58)) { COL2R_ON(); }
            if ((i == 3)||(i == 11)||(i == 19)||(i == 27)||(i == 35)||(i == 43)||(i == 51)||(i == 59)) { COL3R_ON(); }
            if ((i == 4)||(i == 12)||(i == 20)||(i == 28)||(i == 36)||(i == 44)||(i == 52)||(i == 60)) { COL4R_ON(); }
            if ((i == 5)||(i == 13)||(i == 21)||(i == 29)||(i == 37)||(i == 45)||(i == 53)||(i == 61)) { COL5R_ON(); }
            if ((i == 6)||(i == 14)||(i == 22)||(i == 30)||(i == 38)||(i == 46)||(i == 54)||(i == 62)) { COL6R_ON(); }
            if ((i == 7)||(i == 15)||(i == 23)||(i == 31)||(i == 39)||(i == 47)||(i == 55)||(i == 63)) { COL7R_ON(); }
            //DELAY
            usec_delay(LED_R[i]);
            //ALL OFF
            ROW0_OFF();
            ROW1_OFF();
            ROW2_OFF();
            ROW3_OFF();
            ROW4_OFF();
            ROW5_OFF();
            ROW6_OFF();
            ROW7_OFF();
            COL0R_OFF();
            COL1R_OFF();
            COL2R_OFF();
            COL3R_OFF();
            COL4R_OFF();
            COL5R_OFF();
            COL6R_OFF();
            COL7R_OFF();
        }
        if (LED_G[i] > 0)
        {
            //ROW ON
            if (i < 8) { ROW0_ON(); }
            if ((i >= 8) && (i < 16)) { ROW1_ON(); }
            if ((i >= 16) && (i < 24)) { ROW2_ON(); }
            if ((i >= 24) && (i < 32)) { ROW3_ON(); }
            if ((i >= 32) && (i < 40)) { ROW4_ON(); }
            if ((i >= 40) && (i < 48)) { ROW5_ON(); }
            if ((i >= 48) && (i < 56)) { ROW6_ON(); }
            if ((i >= 56) && (i < 64)) { ROW7_ON(); }
            //COL ON
            if ((i == 0)||(i == 8)||(i == 16)||(i == 24)||(i == 32)||(i == 40)||(i == 48)||(i == 56)) { COL0G_ON(); }
            if ((i == 1)||(i == 9)||(i == 17)||(i == 25)||(i == 33)||(i == 41)||(i == 49)||(i == 57)) { COL1G_ON(); }
            if ((i == 2)||(i == 10)||(i == 18)||(i == 26)||(i == 34)||(i == 42)||(i == 50)||(i == 58)) { COL2G_ON(); }
            if ((i == 3)||(i == 11)||(i == 19)||(i == 27)||(i == 35)||(i == 43)||(i == 51)||(i == 59)) { COL3G_ON(); }
            if ((i == 4)||(i == 12)||(i == 20)||(i == 28)||(i == 36)||(i == 44)||(i == 52)||(i == 60)) { COL4G_ON(); }
            if ((i == 5)||(i == 13)||(i == 21)||(i == 29)||(i == 37)||(i == 45)||(i == 53)||(i == 61)) { COL5G_ON(); }
            if ((i == 6)||(i == 14)||(i == 22)||(i == 30)||(i == 38)||(i == 46)||(i == 54)||(i == 62)) { COL6G_ON(); }
            if ((i == 7)||(i == 15)||(i == 23)||(i == 31)||(i == 39)||(i == 47)||(i == 55)||(i == 63)) { COL7G_ON(); }
            //DELAY
            usec_delay(LED_G[i]);
            //ALL OFF
            ROW0_OFF();
            ROW1_OFF();
            ROW2_OFF();
            ROW3_OFF();
            ROW4_OFF();
            ROW5_OFF();
            ROW6_OFF();
            ROW7_OFF();
            COL0G_OFF();
            COL1G_OFF();
            COL2G_OFF();
            COL3G_OFF();
            COL4G_OFF();
            COL5G_OFF();
            COL6G_OFF();
            COL7G_OFF();
        }
        if (LED_B[i] > 0)
        {
            //ROW ON
            if (i < 8) { ROW0_ON(); }
            if ((i >= 8) && (i < 16)) { ROW1_ON(); }
            if ((i >= 16) && (i < 24)) { ROW2_ON(); }
            if ((i >= 24) && (i < 32)) { ROW3_ON(); }
            if ((i >= 32) && (i < 40)) { ROW4_ON(); }
            if ((i >= 40) && (i < 48)) { ROW5_ON(); }
            if ((i >= 48) && (i < 56)) { ROW6_ON(); }
            if ((i >= 56) && (i < 64)) { ROW7_ON(); }
            //COL ON
            if ((i == 0)||(i == 8)||(i == 16)||(i == 24)||(i == 32)||(i == 40)||(i == 48)||(i == 56)) { COL0B_ON(); }
            if ((i == 1)||(i == 9)||(i == 17)||(i == 25)||(i == 33)||(i == 41)||(i == 49)||(i == 57)) { COL1B_ON(); }
            if ((i == 2)||(i == 10)||(i == 18)||(i == 26)||(i == 34)||(i == 42)||(i == 50)||(i == 58)) { COL2B_ON(); }
            if ((i == 3)||(i == 11)||(i == 19)||(i == 27)||(i == 35)||(i == 43)||(i == 51)||(i == 59)) { COL3B_ON(); }
            if ((i == 4)||(i == 12)||(i == 20)||(i == 28)||(i == 36)||(i == 44)||(i == 52)||(i == 60)) { COL4B_ON(); }
            if ((i == 5)||(i == 13)||(i == 21)||(i == 29)||(i == 37)||(i == 45)||(i == 53)||(i == 61)) { COL5B_ON(); }
            if ((i == 6)||(i == 14)||(i == 22)||(i == 30)||(i == 38)||(i == 46)||(i == 54)||(i == 62)) { COL6B_ON(); }
            if ((i == 7)||(i == 15)||(i == 23)||(i == 31)||(i == 39)||(i == 47)||(i == 55)||(i == 63)) { COL7B_ON(); }
            //DELAY
            usec_delay(LED_B[i]);
            //ALL OFF
            ROW0_OFF();
            ROW1_OFF();
            ROW2_OFF();
            ROW3_OFF();
            ROW4_OFF();
            ROW5_OFF();
            ROW6_OFF();
            ROW7_OFF();
            COL0B_OFF();
            COL1B_OFF();
            COL2B_OFF();
            COL3B_OFF();
            COL4B_OFF();
            COL5B_OFF();
            COL6B_OFF();
            COL7B_OFF();
        }
        if ((LED_R[i] == 0)&&(LED_G[i] == 0)&&(LED_B[i] == 0))
        {
            // LED IS OFF BUT WE STILL NEED A DELAY
            //usec_delay((current_red_level + current_green_level + current_blue_level)/100);
            usec_delay(2);
        }
    }
}

//******************************************************************************
void strobe_all()
{
    unsigned char x;
    
    delay_ptr=0;
    x=0x80;
    while(x)
    {
        big_switch_rows(x); 
        x >>= 1;//shift bit one to the right
    
        //if full packet received then process packet
    }    
}

//******************************************************************************
void all_off()
{
    //ALL OFF
    ROW0_OFF();
    ROW1_OFF();
    ROW2_OFF();
    ROW3_OFF();
    ROW4_OFF();
    ROW5_OFF();
    ROW6_OFF();
    ROW7_OFF();
    COL0R_OFF();
    COL1R_OFF();
    COL2R_OFF();
    COL3R_OFF();
    COL4R_OFF();
    COL5R_OFF();
    COL6R_OFF();
    COL7R_OFF();
    COL0G_OFF();
    COL1G_OFF();
    COL2G_OFF();
    COL3G_OFF();
    COL4G_OFF();
    COL5G_OFF();
    COL6G_OFF();
    COL7G_OFF();
    COL0B_OFF();
    COL1B_OFF();
    COL2B_OFF();
    COL3B_OFF();
    COL4B_OFF();
    COL5B_OFF();
    COL6B_OFF();
    COL7B_OFF();

}

void all_on(unsigned char ao)
{
    // ao determines RGB on/off values (may change this later)
    // 0x01 R, 0x02 G, 0x04 B
    // R ON if ao == 0x01 0x03 0x05 0x07
    // G ON if ao == 0x02 0x03 0x06 0x07
    // B ON if ao == 0x04 0x05 0x06 0x07
    
    unsigned char r;
    unsigned char usec;
    
    // delay value
    if ((ao == 0x01)||(ao == 0x02)||(ao == 0x04)) usec = 90;
    if ((ao == 0x03)||(ao == 0x05)||(ao == 0x06)) usec = 45;
    if (ao == 0x07) usec = 30;
    
    for(r=0; r<8; r++)
    {
        switch (r) {
            case 0:
                RB1_ROW0_SetHigh();//turn on row0
                break;
            case 1:
                RB2_ROW1_SetHigh();//turn on row1
                break;
            case 2:
                RB3_ROW2_SetHigh();//turn on row2
                break;
            case 3:
                RB4_ROW3_SetHigh();//turn on row3
                break;
            case 4:
                RB5_ROW4_SetHigh();//turn on row4
                break;
            case 5:
                RB6_ROW5_SetHigh();//turn on row5
                break;
            case 6:
                RB7_ROW6_SetHigh();//turn on row6
                break;
            case 7:
                RC1_ROW7_SetHigh();//turn on row7
                break;
        };

        // COL1
        if ((ao == 0x01)||(ao == 0x03)||(ao == 0x05)||(ao == 0x07)) {
            RD0_C1R_SetLow();//turn on column 1
            usec_delay(usec);
        }    
        RD0_C1R_SetHigh();//turn off column 1
        if ((ao == 0x02)||(ao == 0x03)||(ao == 0x06)||(ao == 0x07)) {
            RD1_C2G_SetLow();//turn on column 2
            usec_delay(usec);
        }
        RD1_C2G_SetHigh();//turn off column 2
        if ((ao == 0x04)||(ao == 0x05)||(ao == 0x06)||(ao == 0x07)) {
            RD2_C3B_SetLow();//turn on column 3
            usec_delay(usec);
        }
        RD2_C3B_SetHigh();//turn off column 3        

        // COL2
        if ((ao == 0x01)||(ao == 0x03)||(ao == 0x05)||(ao == 0x07)) {
            RD3_C4R_SetLow();//turn on column 4
            usec_delay(usec);
        }
        RD3_C4R_SetHigh();//turn off column 4
        if ((ao == 0x02)||(ao == 0x03)||(ao == 0x06)||(ao == 0x07)) {
            RD4_C5G_SetLow();//turn on column 5
            usec_delay(usec);
        }
        RD4_C5G_SetHigh();//turn off column 5
        if ((ao == 0x04)||(ao == 0x05)||(ao == 0x06)||(ao == 0x07)) {
            RD5_C6B_SetLow();//turn on column 6
            usec_delay(usec); 
        }
        RD5_C6B_SetHigh();//turn off column 6

        // COL3        
        if ((ao == 0x01)||(ao == 0x03)||(ao == 0x05)||(ao == 0x07)) {
            RD6_C7R_SetLow();//turn on column 7
            usec_delay(usec);
        }
        RD6_C7R_SetHigh();//turn off column 7
        if ((ao == 0x02)||(ao == 0x03)||(ao == 0x06)||(ao == 0x07)) {
            RD7_C8G_SetLow();//turn on column 8
            usec_delay(usec);
        }
        RD7_C8G_SetHigh();//turn off column 8
        if ((ao == 0x04)||(ao == 0x05)||(ao == 0x06)||(ao == 0x07)) {
            RE0_C9B_SetLow();//turn on column 9
            usec_delay(usec);
        }
        RE0_C9B_SetHigh();//turn off column 9
    
        // COL4
        if ((ao == 0x01)||(ao == 0x03)||(ao == 0x05)||(ao == 0x07)) {
            RE1_C10R_SetLow();//turn on column 10
            usec_delay(usec);
        }
        RE1_C10R_SetHigh();//turn off column 10
        if ((ao == 0x02)||(ao == 0x03)||(ao == 0x06)||(ao == 0x07)) {
            RE2_C11G_SetLow();//turn on column 11
            usec_delay(usec);
        }
        RE2_C11G_SetHigh();//turn off column 11
        if ((ao == 0x04)||(ao == 0x05)||(ao == 0x06)||(ao == 0x07)) {
            RE3_C12B_SetLow();//turn on column 12
            usec_delay(usec);
        }
        RE3_C12B_SetHigh();//turn off column 12
    
        // COL5
        if ((ao == 0x01)||(ao == 0x03)||(ao == 0x05)||(ao == 0x07)) {
            RE4_C13R_SetLow();//turn on column 13
            usec_delay(usec);
        }
        RE4_C13R_SetHigh();//turn off column 13
        if ((ao == 0x02)||(ao == 0x03)||(ao == 0x06)||(ao == 0x07)) {
            RE5_C14G_SetLow();//turn on column 14
            usec_delay(usec);
        }
        RE5_C14G_SetHigh();//turn off column 14
        if ((ao == 0x04)||(ao == 0x05)||(ao == 0x06)||(ao == 0x07)) {
            RE6_C15B_SetLow();//turn on column 15
            usec_delay(usec);
        }
        RE6_C15B_SetHigh();//turn off column 15
    
        // COL6
        if ((ao == 0x01)||(ao == 0x03)||(ao == 0x05)||(ao == 0x07)) {
            RE7_C16R_SetLow();//turn on column 16
            usec_delay(usec);
        }
        RE7_C16R_SetHigh();//turn off column 16
        if ((ao == 0x02)||(ao == 0x03)||(ao == 0x06)||(ao == 0x07)) {
            RF0_C17G_SetLow();//turn on column 17
            usec_delay(usec);
        }
        RF0_C17G_SetHigh();//turn off column 17
        if ((ao == 0x04)||(ao == 0x05)||(ao == 0x06)||(ao == 0x07)) {
            RF1_C18B_SetLow();//turn on column 18
            usec_delay(usec);
        }
        RF1_C18B_SetHigh();//turn off column 18
    
        // COL7
        if ((ao == 0x01)||(ao == 0x03)||(ao == 0x05)||(ao == 0x07)) {
            RF2_C19R_SetLow();//turn on column 19
            usec_delay(usec);
        }
        RF2_C19R_SetHigh();//turn off column 19
        if ((ao == 0x02)||(ao == 0x03)||(ao == 0x06)||(ao == 0x07)) {
            RF3_C20G_SetLow();//turn on column 20
            usec_delay(usec);
        }
        RF3_C20G_SetHigh();//turn off column 20
        if ((ao == 0x04)||(ao == 0x05)||(ao == 0x06)||(ao == 0x07)) {
            RF4_C21B_SetLow();//turn on column 21
            usec_delay(usec);
        }
        RF4_C21B_SetHigh();//turn off column 21
    
        // COL8
        if ((ao == 0x01)||(ao == 0x03)||(ao == 0x05)||(ao == 0x07)) {
            RF5_C22R_SetLow();//turn on column 22
            usec_delay(usec);
        }
        RF5_C22R_SetHigh();//turn off column 22
        if ((ao == 0x02)||(ao == 0x03)||(ao == 0x06)||(ao == 0x07)) {
            RF6_C23G_SetLow();//turn on column 23
            usec_delay(usec);
        }
        RF6_C23G_SetHigh();//turn off column 23
        if ((ao == 0x04)||(ao == 0x05)||(ao == 0x06)||(ao == 0x07)) {
            RF7_C24B_SetLow();//turn on column 24
            usec_delay(usec);
        }
        RF7_C24B_SetHigh();//turn off column 24

        RB1_ROW0_SetLow();//turn off row0
        RB2_ROW1_SetLow();//turn off row1
        RB3_ROW2_SetLow();//turn off row2
        RB4_ROW3_SetLow();//turn off row3
        RB5_ROW4_SetLow();//turn off row4
        RB6_ROW5_SetLow();//turn off row5
        RB7_ROW6_SetLow();//turn off row6
        RC1_ROW7_SetLow();//turn off row7
        
    }
    
}

//******************************************************************************
void test_pattern()
{
//    all_off();

    unsigned char r;
    
    // RED
    for(r=90000; r>0; r--)
    {
        all_on(0x01);
    }
    // GREEN
    for(r=90000; r>0; r--)
    {
        all_on(0x02);
    }
    // BLUE
    for(r=90000; r>0; r--)
    {
        all_on(0x04);
    }
    // RED AND GREEN
    for(r=90000; r>0; r--)
    {
        all_on(0x03);
    }
    // RED AND BLUE
    for(r=90000; r>0; r--)
    {
        all_on(0x05);
    }
    // GREEN AND BLUE
    for(r=90000; r>0; r--)
    {
        all_on(0x06);
    }
    // RED AND GREEN AND BLUE
    for(r=90000; r>0; r--)
    {
        all_on(0x07);
    }
    
}

//******************************************************************************
void big_switch_rows(unsigned char pos)
{
    if(pos & 0x80)//row 1 ROW0
    {
        RC1_ROW7_SetLow();//turn off row7
        RB1_ROW0_SetHigh();//turn on row0
    }
    else if(pos & 0x40)//row 2 ROW1
    {
        RB1_ROW0_SetLow();//turn off row0
        RB2_ROW1_SetHigh();//turn on row1
    }
    else if(pos & 0x20)//row 3 ROW2
    {
        RB2_ROW1_SetLow();//turn off row1
        RB3_ROW2_SetHigh();//turn on row2
    }
    else if(pos & 0x10)//row 4 ROW3
    {
        RB3_ROW2_SetLow();//turn off row2
        RB4_ROW3_SetHigh();//turn on row3
    }
    else if(pos & 0x08)//row 5 ROW4
    {
        RB4_ROW3_SetLow();//turn off row3
        RB5_ROW4_SetHigh();//turn on row4
    }
    else if(pos & 0x04)//row 6 ROW5
    {
        RB5_ROW4_SetLow();//turn off row4
        RB6_ROW5_SetHigh();//turn on row5
    }
    else if(pos & 0x02)//row 7 ROW6
    {
        RB6_ROW5_SetLow();//turn off row5
        RB7_ROW6_SetHigh();//turn on row6
    }
    else if(pos & 0x01)//row 8 ROW7
    {
        RB7_ROW6_SetLow();//turn off row6
        RC1_ROW7_SetHigh();//turn on row7
    }

    big_switch_columns();

}

//******************************************************************************
void big_switch_columns()
{
    RF7_C24B_SetHigh();//turn off column 24
    RD0_C1R_SetLow();//turn on column 1
 //   while(1);
    my_delay(delay_time[delay_ptr++]);    //delay    
    RD0_C1R_SetHigh();//turn off column 1
    RD1_C2G_SetLow();//turn on column 2
    my_delay(delay_time[delay_ptr++]);    //delay    
    RD1_C2G_SetHigh();//turn off column 2
    RD2_C3B_SetLow();//turn on column 3
    my_delay(delay_time[delay_ptr++]);    //delay    
    RD2_C3B_SetHigh();//turn off column 3
    RD3_C4R_SetLow();//turn on column 4
    my_delay(delay_time[delay_ptr++]);    //delay    
    RD3_C4R_SetHigh();//turn off column 4
    RD4_C5G_SetLow();//turn on column 5
    my_delay(delay_time[delay_ptr++]);    //delay    
    RD4_C5G_SetHigh();//turn off column 5
    RD5_C6B_SetLow();//turn on column 6
    my_delay(delay_time[delay_ptr++]);    //delay    
    RD5_C6B_SetHigh();//turn off column 6
    RD6_C7R_SetLow();//turn on column 7
    my_delay(delay_time[delay_ptr++]);    //delay    
    RD6_C7R_SetHigh();//turn off column 7
    RD7_C8G_SetLow();//turn on column 8
    my_delay(delay_time[delay_ptr++]);    //delay    
    RD7_C8G_SetHigh();//turn off column 8
    RE0_C9B_SetLow();//turn on column 9
    my_delay(delay_time[delay_ptr++]);    //delay    
    RE0_C9B_SetHigh();//turn off column 9
    RE1_C10R_SetLow();//turn on column 10
    my_delay(delay_time[delay_ptr++]);    //delay    
    RE1_C10R_SetHigh();//turn off column 10
    RE2_C11G_SetLow();//turn on column 11
    my_delay(delay_time[delay_ptr++]);    //delay    
    RE2_C11G_SetHigh();//turn off column 11
    RE3_C12B_SetLow();//turn on column 12
    my_delay(delay_time[delay_ptr++]);    //delay    
    RE3_C12B_SetHigh();//turn off column 12
    RE4_C13R_SetLow();//turn on column 13
    my_delay(delay_time[delay_ptr++]);    //delay    
    RE4_C13R_SetHigh();//turn off column 13
    RE5_C14G_SetLow();//turn on column 14
    my_delay(delay_time[delay_ptr++]);    //delay    
    RE5_C14G_SetHigh();//turn off column 14
    RE6_C15B_SetLow();//turn on column 15
    my_delay(delay_time[delay_ptr++]);    //delay    
    RE6_C15B_SetHigh();//turn off column 15
    RE7_C16R_SetLow();//turn on column 16
    my_delay(delay_time[delay_ptr++]);    //delay    
    RE7_C16R_SetHigh();//turn off column 16
    RF0_C17G_SetLow();//turn on column 17
    my_delay(delay_time[delay_ptr++]);    //delay    
    RF0_C17G_SetHigh();//turn off column 17
    RF1_C18B_SetLow();//turn on column 18
    my_delay(delay_time[delay_ptr++]);    //delay    
    RF1_C18B_SetHigh();//turn off column 18
    RF2_C19R_SetLow();//turn on column 19
    my_delay(delay_time[delay_ptr++]);    //delay    
    RF2_C19R_SetHigh();//turn off column 19
    RF3_C20G_SetLow();
    my_delay(delay_time[delay_ptr++]);    //delay    
    RF3_C20G_SetHigh();//turn off column 20
    RF4_C21B_SetLow();//turn on column 21
    my_delay(delay_time[delay_ptr++]);    //delay    
    RF4_C21B_SetHigh();//turn off column 21
    RF5_C22R_SetLow();//turn on column 22
    my_delay(delay_time[delay_ptr++]);    //delay    
    RF5_C22R_SetHigh();//turn off column 22
    RF6_C23G_SetLow();//turn on column 23
    my_delay(delay_time[delay_ptr++]);    //delay    
    RF6_C23G_SetHigh();//turn off column 23
    RF7_C24B_SetLow();//turn on column 24
    my_delay(delay_time[delay_ptr++]);    //delay        
}

//******************************************************************************
void usec_delay(unsigned int usec)
{
    while (usec > 0) {
        __delay_us(1);
        usec--;
    }
}


//******************************************************************************
void my_delay(unsigned char dly)
{
    unsigned char volatile x;
    //perform delay...
    
    for(x=0; x<dly; x++);
        //__delay_us(10);
//__delay_ms(1);
}

/**
 End of File
 */

