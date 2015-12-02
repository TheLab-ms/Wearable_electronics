/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using MPLAB� Code Configurator

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB� Code Configurator - v2.25.2
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


//*********** Globals **************************************
unsigned char current_column_position;
unsigned char delay_ptr;
unsigned char delay_time[192];

//*********** Prototypes **************************************
void strobe_all();
void big_switch_rows(unsigned char pos);
void big_switch_columns();
void all_off();
void all_on(unsigned char ao);
void test_pattern();
void usec_delay(unsigned char usec);
void my_delay(unsigned char dly);


//******************************************************************************
void main(void) 
{
    unsigned char x;
    
    SYSTEM_Initialize();// initialize the device

    
    
    //INTERRUPT_GlobalInterruptEnable();// Enable
    //INTERRUPT_PeripheralInterruptEnable();// Enable
    //INTERRUPT_GlobalInterruptDisable();// Disable
    //INTERRUPT_PeripheralInterruptDisable();// Disable

    //init delay times
    for(x=0; x<192; x++)
        delay_time[x] = 100;

    for(x=0; x<192; x+=3)//red
    {
        delay_time[x] = 100;
        delay_time[x+1] = 0;
        delay_time[x+2] = 0;
    }
    
    while (1) 
    {
//        strobe_all();
        test_pattern();
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
    RB1_ROW0_SetLow();//turn off row0
    RB2_ROW1_SetLow();//turn off row1
    RB3_ROW2_SetLow();//turn off row2
    RB4_ROW3_SetLow();//turn off row3
    RB5_ROW4_SetLow();//turn off row4
    RB6_ROW5_SetLow();//turn off row5
    RB7_ROW6_SetLow();//turn off row6
    RC1_ROW7_SetLow();//turn off row7
   
    RD0_C1R_SetHigh();//turn off column 1
    RD1_C2G_SetHigh();//turn off column 2
    RD2_C3B_SetHigh();//turn off column 3
    RD3_C4R_SetHigh();//turn off column 4
    RD4_C5G_SetHigh();//turn off column 5
    RD5_C6B_SetHigh();//turn off column 6
    RD6_C7R_SetHigh();//turn off column 7
    RD7_C8G_SetHigh();//turn off column 8
    RE0_C9B_SetHigh();//turn off column 9
    RE1_C10R_SetHigh();//turn off column 10
    RE2_C11G_SetHigh();//turn off column 11
    RE3_C12B_SetHigh();//turn off column 12
    RE4_C13R_SetHigh();//turn off column 13
    RE5_C14G_SetHigh();//turn off column 14
    RE6_C15B_SetHigh();//turn off column 15
    RE7_C16R_SetHigh();//turn off column 16
    RF0_C17G_SetHigh();//turn off column 17
    RF1_C18B_SetHigh();//turn off column 18
    RF2_C19R_SetHigh();//turn off column 19
    RF3_C20G_SetHigh();//turn off column 20
    RF4_C21B_SetHigh();//turn off column 21
    RF5_C22R_SetHigh();//turn off column 22
    RF6_C23G_SetHigh();//turn off column 23
    RF7_C24B_SetHigh();//turn off column 24
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
void usec_delay(unsigned char usec)
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

