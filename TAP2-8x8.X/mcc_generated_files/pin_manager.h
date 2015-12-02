/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using MPLAB® Code Configurator

  @Description:
    This header file provides implementations for pin APIs for all pins selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB® Code Configurator - v2.25.2
        Device            :  PIC16F1947
        Version           :  1.01
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

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set IO_RA0 aliases
#define IO_RA0_TRIS               TRISA0
#define IO_RA0_LAT                LATA0
#define IO_RA0_PORT               RA0
#define IO_RA0_ANS                ANSA0
#define IO_RA0_SetHigh()    do { LATA0 = 1; } while(0)
#define IO_RA0_SetLow()   do { LATA0 = 0; } while(0)
#define IO_RA0_Toggle()   do { LATA0 = ~LATA0; } while(0)
#define IO_RA0_GetValue()         RA0
#define IO_RA0_SetDigitalInput()    do { TRISA0 = 1; } while(0)
#define IO_RA0_SetDigitalOutput()   do { TRISA0 = 0; } while(0)

#define IO_RA0_SetAnalogMode()   do { ANSA0 = 1; } while(0)
#define IO_RA0_SetDigitalMode()   do { ANSA0 = 0; } while(0)
// get/set IO_RA1 aliases
#define IO_RA1_TRIS               TRISA1
#define IO_RA1_LAT                LATA1
#define IO_RA1_PORT               RA1
#define IO_RA1_ANS                ANSA1
#define IO_RA1_SetHigh()    do { LATA1 = 1; } while(0)
#define IO_RA1_SetLow()   do { LATA1 = 0; } while(0)
#define IO_RA1_Toggle()   do { LATA1 = ~LATA1; } while(0)
#define IO_RA1_GetValue()         RA1
#define IO_RA1_SetDigitalInput()    do { TRISA1 = 1; } while(0)
#define IO_RA1_SetDigitalOutput()   do { TRISA1 = 0; } while(0)

#define IO_RA1_SetAnalogMode()   do { ANSA1 = 1; } while(0)
#define IO_RA1_SetDigitalMode()   do { ANSA1 = 0; } while(0)
// get/set IO_RA2 aliases
#define IO_RA2_TRIS               TRISA2
#define IO_RA2_LAT                LATA2
#define IO_RA2_PORT               RA2
#define IO_RA2_ANS                ANSA2
#define IO_RA2_SetHigh()    do { LATA2 = 1; } while(0)
#define IO_RA2_SetLow()   do { LATA2 = 0; } while(0)
#define IO_RA2_Toggle()   do { LATA2 = ~LATA2; } while(0)
#define IO_RA2_GetValue()         RA2
#define IO_RA2_SetDigitalInput()    do { TRISA2 = 1; } while(0)
#define IO_RA2_SetDigitalOutput()   do { TRISA2 = 0; } while(0)

#define IO_RA2_SetAnalogMode()   do { ANSA2 = 1; } while(0)
#define IO_RA2_SetDigitalMode()   do { ANSA2 = 0; } while(0)
// get/set IO_RA3 aliases
#define IO_RA3_TRIS               TRISA3
#define IO_RA3_LAT                LATA3
#define IO_RA3_PORT               RA3
#define IO_RA3_ANS                ANSA3
#define IO_RA3_SetHigh()    do { LATA3 = 1; } while(0)
#define IO_RA3_SetLow()   do { LATA3 = 0; } while(0)
#define IO_RA3_Toggle()   do { LATA3 = ~LATA3; } while(0)
#define IO_RA3_GetValue()         RA3
#define IO_RA3_SetDigitalInput()    do { TRISA3 = 1; } while(0)
#define IO_RA3_SetDigitalOutput()   do { TRISA3 = 0; } while(0)

#define IO_RA3_SetAnalogMode()   do { ANSA3 = 1; } while(0)
#define IO_RA3_SetDigitalMode()   do { ANSA3 = 0; } while(0)
// get/set IO_RA4 aliases
#define IO_RA4_TRIS               TRISA4
#define IO_RA4_LAT                LATA4
#define IO_RA4_PORT               RA4
#define IO_RA4_SetHigh()    do { LATA4 = 1; } while(0)
#define IO_RA4_SetLow()   do { LATA4 = 0; } while(0)
#define IO_RA4_Toggle()   do { LATA4 = ~LATA4; } while(0)
#define IO_RA4_GetValue()         RA4
#define IO_RA4_SetDigitalInput()    do { TRISA4 = 1; } while(0)
#define IO_RA4_SetDigitalOutput()   do { TRISA4 = 0; } while(0)

// get/set IO_RA5 aliases
#define IO_RA5_TRIS               TRISA5
#define IO_RA5_LAT                LATA5
#define IO_RA5_PORT               RA5
#define IO_RA5_ANS                ANSA5
#define IO_RA5_SetHigh()    do { LATA5 = 1; } while(0)
#define IO_RA5_SetLow()   do { LATA5 = 0; } while(0)
#define IO_RA5_Toggle()   do { LATA5 = ~LATA5; } while(0)
#define IO_RA5_GetValue()         RA5
#define IO_RA5_SetDigitalInput()    do { TRISA5 = 1; } while(0)
#define IO_RA5_SetDigitalOutput()   do { TRISA5 = 0; } while(0)

#define IO_RA5_SetAnalogMode()   do { ANSA5 = 1; } while(0)
#define IO_RA5_SetDigitalMode()   do { ANSA5 = 0; } while(0)
// get/set IO_RA6 aliases
#define IO_RA6_TRIS               TRISA6
#define IO_RA6_LAT                LATA6
#define IO_RA6_PORT               RA6
#define IO_RA6_SetHigh()    do { LATA6 = 1; } while(0)
#define IO_RA6_SetLow()   do { LATA6 = 0; } while(0)
#define IO_RA6_Toggle()   do { LATA6 = ~LATA6; } while(0)
#define IO_RA6_GetValue()         RA6
#define IO_RA6_SetDigitalInput()    do { TRISA6 = 1; } while(0)
#define IO_RA6_SetDigitalOutput()   do { TRISA6 = 0; } while(0)

// get/set IO_RA7 aliases
#define IO_RA7_TRIS               TRISA7
#define IO_RA7_LAT                LATA7
#define IO_RA7_PORT               RA7
#define IO_RA7_SetHigh()    do { LATA7 = 1; } while(0)
#define IO_RA7_SetLow()   do { LATA7 = 0; } while(0)
#define IO_RA7_Toggle()   do { LATA7 = ~LATA7; } while(0)
#define IO_RA7_GetValue()         RA7
#define IO_RA7_SetDigitalInput()    do { TRISA7 = 1; } while(0)
#define IO_RA7_SetDigitalOutput()   do { TRISA7 = 0; } while(0)

// get/set RB0_DLATCH aliases
#define RB0_DLATCH_TRIS               TRISB0
#define RB0_DLATCH_LAT                LATB0
#define RB0_DLATCH_PORT               RB0
#define RB0_DLATCH_WPU                WPUB0
#define RB0_DLATCH_SetHigh()    do { LATB0 = 1; } while(0)
#define RB0_DLATCH_SetLow()   do { LATB0 = 0; } while(0)
#define RB0_DLATCH_Toggle()   do { LATB0 = ~LATB0; } while(0)
#define RB0_DLATCH_GetValue()         RB0
#define RB0_DLATCH_SetDigitalInput()    do { TRISB0 = 1; } while(0)
#define RB0_DLATCH_SetDigitalOutput()   do { TRISB0 = 0; } while(0)

#define RB0_DLATCH_SetPullup()    do { WPUB0 = 1; } while(0)
#define RB0_DLATCH_ResetPullup()   do { WPUB0 = 0; } while(0)
// get/set RB1_ROW0 aliases
#define RB1_ROW0_TRIS               TRISB1
#define RB1_ROW0_LAT                LATB1
#define RB1_ROW0_PORT               RB1
#define RB1_ROW0_WPU                WPUB1
#define RB1_ROW0_SetHigh()    do { LATB1 = 1; } while(0)
#define RB1_ROW0_SetLow()   do { LATB1 = 0; } while(0)
#define RB1_ROW0_Toggle()   do { LATB1 = ~LATB1; } while(0)
#define RB1_ROW0_GetValue()         RB1
#define RB1_ROW0_SetDigitalInput()    do { TRISB1 = 1; } while(0)
#define RB1_ROW0_SetDigitalOutput()   do { TRISB1 = 0; } while(0)

#define RB1_ROW0_SetPullup()    do { WPUB1 = 1; } while(0)
#define RB1_ROW0_ResetPullup()   do { WPUB1 = 0; } while(0)
// get/set RB2_ROW1 aliases
#define RB2_ROW1_TRIS               TRISB2
#define RB2_ROW1_LAT                LATB2
#define RB2_ROW1_PORT               RB2
#define RB2_ROW1_WPU                WPUB2
#define RB2_ROW1_SetHigh()    do { LATB2 = 1; } while(0)
#define RB2_ROW1_SetLow()   do { LATB2 = 0; } while(0)
#define RB2_ROW1_Toggle()   do { LATB2 = ~LATB2; } while(0)
#define RB2_ROW1_GetValue()         RB2
#define RB2_ROW1_SetDigitalInput()    do { TRISB2 = 1; } while(0)
#define RB2_ROW1_SetDigitalOutput()   do { TRISB2 = 0; } while(0)

#define RB2_ROW1_SetPullup()    do { WPUB2 = 1; } while(0)
#define RB2_ROW1_ResetPullup()   do { WPUB2 = 0; } while(0)
// get/set RB3_ROW2 aliases
#define RB3_ROW2_TRIS               TRISB3
#define RB3_ROW2_LAT                LATB3
#define RB3_ROW2_PORT               RB3
#define RB3_ROW2_WPU                WPUB3
#define RB3_ROW2_SetHigh()    do { LATB3 = 1; } while(0)
#define RB3_ROW2_SetLow()   do { LATB3 = 0; } while(0)
#define RB3_ROW2_Toggle()   do { LATB3 = ~LATB3; } while(0)
#define RB3_ROW2_GetValue()         RB3
#define RB3_ROW2_SetDigitalInput()    do { TRISB3 = 1; } while(0)
#define RB3_ROW2_SetDigitalOutput()   do { TRISB3 = 0; } while(0)

#define RB3_ROW2_SetPullup()    do { WPUB3 = 1; } while(0)
#define RB3_ROW2_ResetPullup()   do { WPUB3 = 0; } while(0)
// get/set RB4_ROW3 aliases
#define RB4_ROW3_TRIS               TRISB4
#define RB4_ROW3_LAT                LATB4
#define RB4_ROW3_PORT               RB4
#define RB4_ROW3_WPU                WPUB4
#define RB4_ROW3_SetHigh()    do { LATB4 = 1; } while(0)
#define RB4_ROW3_SetLow()   do { LATB4 = 0; } while(0)
#define RB4_ROW3_Toggle()   do { LATB4 = ~LATB4; } while(0)
#define RB4_ROW3_GetValue()         RB4
#define RB4_ROW3_SetDigitalInput()    do { TRISB4 = 1; } while(0)
#define RB4_ROW3_SetDigitalOutput()   do { TRISB4 = 0; } while(0)

#define RB4_ROW3_SetPullup()    do { WPUB4 = 1; } while(0)
#define RB4_ROW3_ResetPullup()   do { WPUB4 = 0; } while(0)
// get/set RB5_ROW4 aliases
#define RB5_ROW4_TRIS               TRISB5
#define RB5_ROW4_LAT                LATB5
#define RB5_ROW4_PORT               RB5
#define RB5_ROW4_WPU                WPUB5
#define RB5_ROW4_SetHigh()    do { LATB5 = 1; } while(0)
#define RB5_ROW4_SetLow()   do { LATB5 = 0; } while(0)
#define RB5_ROW4_Toggle()   do { LATB5 = ~LATB5; } while(0)
#define RB5_ROW4_GetValue()         RB5
#define RB5_ROW4_SetDigitalInput()    do { TRISB5 = 1; } while(0)
#define RB5_ROW4_SetDigitalOutput()   do { TRISB5 = 0; } while(0)

#define RB5_ROW4_SetPullup()    do { WPUB5 = 1; } while(0)
#define RB5_ROW4_ResetPullup()   do { WPUB5 = 0; } while(0)
// get/set RB6_ROW5 aliases
#define RB6_ROW5_TRIS               TRISB6
#define RB6_ROW5_LAT                LATB6
#define RB6_ROW5_PORT               RB6
#define RB6_ROW5_WPU                WPUB6
#define RB6_ROW5_SetHigh()    do { LATB6 = 1; } while(0)
#define RB6_ROW5_SetLow()   do { LATB6 = 0; } while(0)
#define RB6_ROW5_Toggle()   do { LATB6 = ~LATB6; } while(0)
#define RB6_ROW5_GetValue()         RB6
#define RB6_ROW5_SetDigitalInput()    do { TRISB6 = 1; } while(0)
#define RB6_ROW5_SetDigitalOutput()   do { TRISB6 = 0; } while(0)

#define RB6_ROW5_SetPullup()    do { WPUB6 = 1; } while(0)
#define RB6_ROW5_ResetPullup()   do { WPUB6 = 0; } while(0)
// get/set RB7_ROW6 aliases
#define RB7_ROW6_TRIS               TRISB7
#define RB7_ROW6_LAT                LATB7
#define RB7_ROW6_PORT               RB7
#define RB7_ROW6_WPU                WPUB7
#define RB7_ROW6_SetHigh()    do { LATB7 = 1; } while(0)
#define RB7_ROW6_SetLow()   do { LATB7 = 0; } while(0)
#define RB7_ROW6_Toggle()   do { LATB7 = ~LATB7; } while(0)
#define RB7_ROW6_GetValue()         RB7
#define RB7_ROW6_SetDigitalInput()    do { TRISB7 = 1; } while(0)
#define RB7_ROW6_SetDigitalOutput()   do { TRISB7 = 0; } while(0)

#define RB7_ROW6_SetPullup()    do { WPUB7 = 1; } while(0)
#define RB7_ROW6_ResetPullup()   do { WPUB7 = 0; } while(0)
// get/set RC1_ROW7 aliases
#define RC1_ROW7_TRIS               TRISC1
#define RC1_ROW7_LAT                LATC1
#define RC1_ROW7_PORT               RC1
#define RC1_ROW7_SetHigh()    do { LATC1 = 1; } while(0)
#define RC1_ROW7_SetLow()   do { LATC1 = 0; } while(0)
#define RC1_ROW7_Toggle()   do { LATC1 = ~LATC1; } while(0)
#define RC1_ROW7_GetValue()         RC1
#define RC1_ROW7_SetDigitalInput()    do { TRISC1 = 1; } while(0)
#define RC1_ROW7_SetDigitalOutput()   do { TRISC1 = 0; } while(0)

// get/set TX1 aliases
#define TX1_TRIS               TRISC6
#define TX1_LAT                LATC6
#define TX1_PORT               RC6
#define TX1_SetHigh()    do { LATC6 = 1; } while(0)
#define TX1_SetLow()   do { LATC6 = 0; } while(0)
#define TX1_Toggle()   do { LATC6 = ~LATC6; } while(0)
#define TX1_GetValue()         RC6
#define TX1_SetDigitalInput()    do { TRISC6 = 1; } while(0)
#define TX1_SetDigitalOutput()   do { TRISC6 = 0; } while(0)

// get/set RX1 aliases
#define RX1_TRIS               TRISC7
#define RX1_LAT                LATC7
#define RX1_PORT               RC7
#define RX1_SetHigh()    do { LATC7 = 1; } while(0)
#define RX1_SetLow()   do { LATC7 = 0; } while(0)
#define RX1_Toggle()   do { LATC7 = ~LATC7; } while(0)
#define RX1_GetValue()         RC7
#define RX1_SetDigitalInput()    do { TRISC7 = 1; } while(0)
#define RX1_SetDigitalOutput()   do { TRISC7 = 0; } while(0)

// get/set RD0_C1R aliases
#define RD0_C1R_TRIS               TRISD0
#define RD0_C1R_LAT                LATD0
#define RD0_C1R_PORT               RD0
#define RD0_C1R_SetHigh()    do { LATD0 = 1; } while(0)
#define RD0_C1R_SetLow()   do { LATD0 = 0; } while(0)
#define RD0_C1R_Toggle()   do { LATD0 = ~LATD0; } while(0)
#define RD0_C1R_GetValue()         RD0
#define RD0_C1R_SetDigitalInput()    do { TRISD0 = 1; } while(0)
#define RD0_C1R_SetDigitalOutput()   do { TRISD0 = 0; } while(0)

// get/set RD1_C2G aliases
#define RD1_C2G_TRIS               TRISD1
#define RD1_C2G_LAT                LATD1
#define RD1_C2G_PORT               RD1
#define RD1_C2G_SetHigh()    do { LATD1 = 1; } while(0)
#define RD1_C2G_SetLow()   do { LATD1 = 0; } while(0)
#define RD1_C2G_Toggle()   do { LATD1 = ~LATD1; } while(0)
#define RD1_C2G_GetValue()         RD1
#define RD1_C2G_SetDigitalInput()    do { TRISD1 = 1; } while(0)
#define RD1_C2G_SetDigitalOutput()   do { TRISD1 = 0; } while(0)

// get/set RD2_C3B aliases
#define RD2_C3B_TRIS               TRISD2
#define RD2_C3B_LAT                LATD2
#define RD2_C3B_PORT               RD2
#define RD2_C3B_SetHigh()    do { LATD2 = 1; } while(0)
#define RD2_C3B_SetLow()   do { LATD2 = 0; } while(0)
#define RD2_C3B_Toggle()   do { LATD2 = ~LATD2; } while(0)
#define RD2_C3B_GetValue()         RD2
#define RD2_C3B_SetDigitalInput()    do { TRISD2 = 1; } while(0)
#define RD2_C3B_SetDigitalOutput()   do { TRISD2 = 0; } while(0)

// get/set RD3_C4R aliases
#define RD3_C4R_TRIS               TRISD3
#define RD3_C4R_LAT                LATD3
#define RD3_C4R_PORT               RD3
#define RD3_C4R_SetHigh()    do { LATD3 = 1; } while(0)
#define RD3_C4R_SetLow()   do { LATD3 = 0; } while(0)
#define RD3_C4R_Toggle()   do { LATD3 = ~LATD3; } while(0)
#define RD3_C4R_GetValue()         RD3
#define RD3_C4R_SetDigitalInput()    do { TRISD3 = 1; } while(0)
#define RD3_C4R_SetDigitalOutput()   do { TRISD3 = 0; } while(0)

// get/set RD4_C5G aliases
#define RD4_C5G_TRIS               TRISD4
#define RD4_C5G_LAT                LATD4
#define RD4_C5G_PORT               RD4
#define RD4_C5G_SetHigh()    do { LATD4 = 1; } while(0)
#define RD4_C5G_SetLow()   do { LATD4 = 0; } while(0)
#define RD4_C5G_Toggle()   do { LATD4 = ~LATD4; } while(0)
#define RD4_C5G_GetValue()         RD4
#define RD4_C5G_SetDigitalInput()    do { TRISD4 = 1; } while(0)
#define RD4_C5G_SetDigitalOutput()   do { TRISD4 = 0; } while(0)

// get/set RD5_C6B aliases
#define RD5_C6B_TRIS               TRISD5
#define RD5_C6B_LAT                LATD5
#define RD5_C6B_PORT               RD5
#define RD5_C6B_SetHigh()    do { LATD5 = 1; } while(0)
#define RD5_C6B_SetLow()   do { LATD5 = 0; } while(0)
#define RD5_C6B_Toggle()   do { LATD5 = ~LATD5; } while(0)
#define RD5_C6B_GetValue()         RD5
#define RD5_C6B_SetDigitalInput()    do { TRISD5 = 1; } while(0)
#define RD5_C6B_SetDigitalOutput()   do { TRISD5 = 0; } while(0)

// get/set RD6_C7R aliases
#define RD6_C7R_TRIS               TRISD6
#define RD6_C7R_LAT                LATD6
#define RD6_C7R_PORT               RD6
#define RD6_C7R_SetHigh()    do { LATD6 = 1; } while(0)
#define RD6_C7R_SetLow()   do { LATD6 = 0; } while(0)
#define RD6_C7R_Toggle()   do { LATD6 = ~LATD6; } while(0)
#define RD6_C7R_GetValue()         RD6
#define RD6_C7R_SetDigitalInput()    do { TRISD6 = 1; } while(0)
#define RD6_C7R_SetDigitalOutput()   do { TRISD6 = 0; } while(0)

// get/set RD7_C8G aliases
#define RD7_C8G_TRIS               TRISD7
#define RD7_C8G_LAT                LATD7
#define RD7_C8G_PORT               RD7
#define RD7_C8G_SetHigh()    do { LATD7 = 1; } while(0)
#define RD7_C8G_SetLow()   do { LATD7 = 0; } while(0)
#define RD7_C8G_Toggle()   do { LATD7 = ~LATD7; } while(0)
#define RD7_C8G_GetValue()         RD7
#define RD7_C8G_SetDigitalInput()    do { TRISD7 = 1; } while(0)
#define RD7_C8G_SetDigitalOutput()   do { TRISD7 = 0; } while(0)

// get/set RE0_C9B aliases
#define RE0_C9B_TRIS               TRISE0
#define RE0_C9B_LAT                LATE0
#define RE0_C9B_PORT               RE0
#define RE0_C9B_ANS                ANSE0
#define RE0_C9B_SetHigh()    do { LATE0 = 1; } while(0)
#define RE0_C9B_SetLow()   do { LATE0 = 0; } while(0)
#define RE0_C9B_Toggle()   do { LATE0 = ~LATE0; } while(0)
#define RE0_C9B_GetValue()         RE0
#define RE0_C9B_SetDigitalInput()    do { TRISE0 = 1; } while(0)
#define RE0_C9B_SetDigitalOutput()   do { TRISE0 = 0; } while(0)

#define RE0_C9B_SetAnalogMode()   do { ANSE0 = 1; } while(0)
#define RE0_C9B_SetDigitalMode()   do { ANSE0 = 0; } while(0)
// get/set RE1_C10R aliases
#define RE1_C10R_TRIS               TRISE1
#define RE1_C10R_LAT                LATE1
#define RE1_C10R_PORT               RE1
#define RE1_C10R_ANS                ANSE1
#define RE1_C10R_SetHigh()    do { LATE1 = 1; } while(0)
#define RE1_C10R_SetLow()   do { LATE1 = 0; } while(0)
#define RE1_C10R_Toggle()   do { LATE1 = ~LATE1; } while(0)
#define RE1_C10R_GetValue()         RE1
#define RE1_C10R_SetDigitalInput()    do { TRISE1 = 1; } while(0)
#define RE1_C10R_SetDigitalOutput()   do { TRISE1 = 0; } while(0)

#define RE1_C10R_SetAnalogMode()   do { ANSE1 = 1; } while(0)
#define RE1_C10R_SetDigitalMode()   do { ANSE1 = 0; } while(0)
// get/set RE2_C11G aliases
#define RE2_C11G_TRIS               TRISE2
#define RE2_C11G_LAT                LATE2
#define RE2_C11G_PORT               RE2
#define RE2_C11G_ANS                ANSE2
#define RE2_C11G_SetHigh()    do { LATE2 = 1; } while(0)
#define RE2_C11G_SetLow()   do { LATE2 = 0; } while(0)
#define RE2_C11G_Toggle()   do { LATE2 = ~LATE2; } while(0)
#define RE2_C11G_GetValue()         RE2
#define RE2_C11G_SetDigitalInput()    do { TRISE2 = 1; } while(0)
#define RE2_C11G_SetDigitalOutput()   do { TRISE2 = 0; } while(0)

#define RE2_C11G_SetAnalogMode()   do { ANSE2 = 1; } while(0)
#define RE2_C11G_SetDigitalMode()   do { ANSE2 = 0; } while(0)
// get/set RE3_C12B aliases
#define RE3_C12B_TRIS               TRISE3
#define RE3_C12B_LAT                LATE3
#define RE3_C12B_PORT               RE3
#define RE3_C12B_SetHigh()    do { LATE3 = 1; } while(0)
#define RE3_C12B_SetLow()   do { LATE3 = 0; } while(0)
#define RE3_C12B_Toggle()   do { LATE3 = ~LATE3; } while(0)
#define RE3_C12B_GetValue()         RE3
#define RE3_C12B_SetDigitalInput()    do { TRISE3 = 1; } while(0)
#define RE3_C12B_SetDigitalOutput()   do { TRISE3 = 0; } while(0)

// get/set RE4_C13R aliases
#define RE4_C13R_TRIS               TRISE4
#define RE4_C13R_LAT                LATE4
#define RE4_C13R_PORT               RE4
#define RE4_C13R_SetHigh()    do { LATE4 = 1; } while(0)
#define RE4_C13R_SetLow()   do { LATE4 = 0; } while(0)
#define RE4_C13R_Toggle()   do { LATE4 = ~LATE4; } while(0)
#define RE4_C13R_GetValue()         RE4
#define RE4_C13R_SetDigitalInput()    do { TRISE4 = 1; } while(0)
#define RE4_C13R_SetDigitalOutput()   do { TRISE4 = 0; } while(0)

// get/set RE5_C14G aliases
#define RE5_C14G_TRIS               TRISE5
#define RE5_C14G_LAT                LATE5
#define RE5_C14G_PORT               RE5
#define RE5_C14G_SetHigh()    do { LATE5 = 1; } while(0)
#define RE5_C14G_SetLow()   do { LATE5 = 0; } while(0)
#define RE5_C14G_Toggle()   do { LATE5 = ~LATE5; } while(0)
#define RE5_C14G_GetValue()         RE5
#define RE5_C14G_SetDigitalInput()    do { TRISE5 = 1; } while(0)
#define RE5_C14G_SetDigitalOutput()   do { TRISE5 = 0; } while(0)

// get/set RE6_C15B aliases
#define RE6_C15B_TRIS               TRISE6
#define RE6_C15B_LAT                LATE6
#define RE6_C15B_PORT               RE6
#define RE6_C15B_SetHigh()    do { LATE6 = 1; } while(0)
#define RE6_C15B_SetLow()   do { LATE6 = 0; } while(0)
#define RE6_C15B_Toggle()   do { LATE6 = ~LATE6; } while(0)
#define RE6_C15B_GetValue()         RE6
#define RE6_C15B_SetDigitalInput()    do { TRISE6 = 1; } while(0)
#define RE6_C15B_SetDigitalOutput()   do { TRISE6 = 0; } while(0)

// get/set RE7_C16R aliases
#define RE7_C16R_TRIS               TRISE7
#define RE7_C16R_LAT                LATE7
#define RE7_C16R_PORT               RE7
#define RE7_C16R_SetHigh()    do { LATE7 = 1; } while(0)
#define RE7_C16R_SetLow()   do { LATE7 = 0; } while(0)
#define RE7_C16R_Toggle()   do { LATE7 = ~LATE7; } while(0)
#define RE7_C16R_GetValue()         RE7
#define RE7_C16R_SetDigitalInput()    do { TRISE7 = 1; } while(0)
#define RE7_C16R_SetDigitalOutput()   do { TRISE7 = 0; } while(0)

// get/set RF0_C17G aliases
#define RF0_C17G_TRIS               TRISF0
#define RF0_C17G_LAT                LATF0
#define RF0_C17G_PORT               RF0
#define RF0_C17G_ANS                ANSF0
#define RF0_C17G_SetHigh()    do { LATF0 = 1; } while(0)
#define RF0_C17G_SetLow()   do { LATF0 = 0; } while(0)
#define RF0_C17G_Toggle()   do { LATF0 = ~LATF0; } while(0)
#define RF0_C17G_GetValue()         RF0
#define RF0_C17G_SetDigitalInput()    do { TRISF0 = 1; } while(0)
#define RF0_C17G_SetDigitalOutput()   do { TRISF0 = 0; } while(0)

#define RF0_C17G_SetAnalogMode()   do { ANSF0 = 1; } while(0)
#define RF0_C17G_SetDigitalMode()   do { ANSF0 = 0; } while(0)
// get/set RF1_C18B aliases
#define RF1_C18B_TRIS               TRISF1
#define RF1_C18B_LAT                LATF1
#define RF1_C18B_PORT               RF1
#define RF1_C18B_ANS                ANSF1
#define RF1_C18B_SetHigh()    do { LATF1 = 1; } while(0)
#define RF1_C18B_SetLow()   do { LATF1 = 0; } while(0)
#define RF1_C18B_Toggle()   do { LATF1 = ~LATF1; } while(0)
#define RF1_C18B_GetValue()         RF1
#define RF1_C18B_SetDigitalInput()    do { TRISF1 = 1; } while(0)
#define RF1_C18B_SetDigitalOutput()   do { TRISF1 = 0; } while(0)

#define RF1_C18B_SetAnalogMode()   do { ANSF1 = 1; } while(0)
#define RF1_C18B_SetDigitalMode()   do { ANSF1 = 0; } while(0)
// get/set RF2_C19R aliases
#define RF2_C19R_TRIS               TRISF2
#define RF2_C19R_LAT                LATF2
#define RF2_C19R_PORT               RF2
#define RF2_C19R_ANS                ANSF2
#define RF2_C19R_SetHigh()    do { LATF2 = 1; } while(0)
#define RF2_C19R_SetLow()   do { LATF2 = 0; } while(0)
#define RF2_C19R_Toggle()   do { LATF2 = ~LATF2; } while(0)
#define RF2_C19R_GetValue()         RF2
#define RF2_C19R_SetDigitalInput()    do { TRISF2 = 1; } while(0)
#define RF2_C19R_SetDigitalOutput()   do { TRISF2 = 0; } while(0)

#define RF2_C19R_SetAnalogMode()   do { ANSF2 = 1; } while(0)
#define RF2_C19R_SetDigitalMode()   do { ANSF2 = 0; } while(0)
// get/set RF3_C20G aliases
#define RF3_C20G_TRIS               TRISF3
#define RF3_C20G_LAT                LATF3
#define RF3_C20G_PORT               RF3
#define RF3_C20G_ANS                ANSF3
#define RF3_C20G_SetHigh()    do { LATF3 = 1; } while(0)
#define RF3_C20G_SetLow()   do { LATF3 = 0; } while(0)
#define RF3_C20G_Toggle()   do { LATF3 = ~LATF3; } while(0)
#define RF3_C20G_GetValue()         RF3
#define RF3_C20G_SetDigitalInput()    do { TRISF3 = 1; } while(0)
#define RF3_C20G_SetDigitalOutput()   do { TRISF3 = 0; } while(0)

#define RF3_C20G_SetAnalogMode()   do { ANSF3 = 1; } while(0)
#define RF3_C20G_SetDigitalMode()   do { ANSF3 = 0; } while(0)
// get/set RF4_C21B aliases
#define RF4_C21B_TRIS               TRISF4
#define RF4_C21B_LAT                LATF4
#define RF4_C21B_PORT               RF4
#define RF4_C21B_ANS                ANSF4
#define RF4_C21B_SetHigh()    do { LATF4 = 1; } while(0)
#define RF4_C21B_SetLow()   do { LATF4 = 0; } while(0)
#define RF4_C21B_Toggle()   do { LATF4 = ~LATF4; } while(0)
#define RF4_C21B_GetValue()         RF4
#define RF4_C21B_SetDigitalInput()    do { TRISF4 = 1; } while(0)
#define RF4_C21B_SetDigitalOutput()   do { TRISF4 = 0; } while(0)

#define RF4_C21B_SetAnalogMode()   do { ANSF4 = 1; } while(0)
#define RF4_C21B_SetDigitalMode()   do { ANSF4 = 0; } while(0)
// get/set RF5_C22R aliases
#define RF5_C22R_TRIS               TRISF5
#define RF5_C22R_LAT                LATF5
#define RF5_C22R_PORT               RF5
#define RF5_C22R_ANS                ANSF5
#define RF5_C22R_SetHigh()    do { LATF5 = 1; } while(0)
#define RF5_C22R_SetLow()   do { LATF5 = 0; } while(0)
#define RF5_C22R_Toggle()   do { LATF5 = ~LATF5; } while(0)
#define RF5_C22R_GetValue()         RF5
#define RF5_C22R_SetDigitalInput()    do { TRISF5 = 1; } while(0)
#define RF5_C22R_SetDigitalOutput()   do { TRISF5 = 0; } while(0)

#define RF5_C22R_SetAnalogMode()   do { ANSF5 = 1; } while(0)
#define RF5_C22R_SetDigitalMode()   do { ANSF5 = 0; } while(0)
// get/set RF6_C23G aliases
#define RF6_C23G_TRIS               TRISF6
#define RF6_C23G_LAT                LATF6
#define RF6_C23G_PORT               RF6
#define RF6_C23G_ANS                ANSF6
#define RF6_C23G_SetHigh()    do { LATF6 = 1; } while(0)
#define RF6_C23G_SetLow()   do { LATF6 = 0; } while(0)
#define RF6_C23G_Toggle()   do { LATF6 = ~LATF6; } while(0)
#define RF6_C23G_GetValue()         RF6
#define RF6_C23G_SetDigitalInput()    do { TRISF6 = 1; } while(0)
#define RF6_C23G_SetDigitalOutput()   do { TRISF6 = 0; } while(0)

#define RF6_C23G_SetAnalogMode()   do { ANSF6 = 1; } while(0)
#define RF6_C23G_SetDigitalMode()   do { ANSF6 = 0; } while(0)
// get/set RF7_C24B aliases
#define RF7_C24B_TRIS               TRISF7
#define RF7_C24B_LAT                LATF7
#define RF7_C24B_PORT               RF7
#define RF7_C24B_ANS                ANSF7
#define RF7_C24B_SetHigh()    do { LATF7 = 1; } while(0)
#define RF7_C24B_SetLow()   do { LATF7 = 0; } while(0)
#define RF7_C24B_Toggle()   do { LATF7 = ~LATF7; } while(0)
#define RF7_C24B_GetValue()         RF7
#define RF7_C24B_SetDigitalInput()    do { TRISF7 = 1; } while(0)
#define RF7_C24B_SetDigitalOutput()   do { TRISF7 = 0; } while(0)

#define RF7_C24B_SetAnalogMode()   do { ANSF7 = 1; } while(0)
#define RF7_C24B_SetDigitalMode()   do { ANSF7 = 0; } while(0)
// get/set RG0_LRN aliases
#define RG0_LRN_TRIS               TRISG0
#define RG0_LRN_LAT                LATG0
#define RG0_LRN_PORT               RG0
#define RG0_LRN_SetHigh()    do { LATG0 = 1; } while(0)
#define RG0_LRN_SetLow()   do { LATG0 = 0; } while(0)
#define RG0_LRN_Toggle()   do { LATG0 = ~LATG0; } while(0)
#define RG0_LRN_GetValue()         RG0
#define RG0_LRN_SetDigitalInput()    do { TRISG0 = 1; } while(0)
#define RG0_LRN_SetDigitalOutput()   do { TRISG0 = 0; } while(0)

// get/set TX2 aliases
#define TX2_TRIS               TRISG1
#define TX2_LAT                LATG1
#define TX2_PORT               RG1
#define TX2_ANS                ANSG1
#define TX2_SetHigh()    do { LATG1 = 1; } while(0)
#define TX2_SetLow()   do { LATG1 = 0; } while(0)
#define TX2_Toggle()   do { LATG1 = ~LATG1; } while(0)
#define TX2_GetValue()         RG1
#define TX2_SetDigitalInput()    do { TRISG1 = 1; } while(0)
#define TX2_SetDigitalOutput()   do { TRISG1 = 0; } while(0)

#define TX2_SetAnalogMode()   do { ANSG1 = 1; } while(0)
#define TX2_SetDigitalMode()   do { ANSG1 = 0; } while(0)
// get/set RX2 aliases
#define RX2_TRIS               TRISG2
#define RX2_LAT                LATG2
#define RX2_PORT               RG2
#define RX2_ANS                ANSG2
#define RX2_SetHigh()    do { LATG2 = 1; } while(0)
#define RX2_SetLow()   do { LATG2 = 0; } while(0)
#define RX2_Toggle()   do { LATG2 = ~LATG2; } while(0)
#define RX2_GetValue()         RG2
#define RX2_SetDigitalInput()    do { TRISG2 = 1; } while(0)
#define RX2_SetDigitalOutput()   do { TRISG2 = 0; } while(0)

#define RX2_SetAnalogMode()   do { ANSG2 = 1; } while(0)
#define RX2_SetDigitalMode()   do { ANSG2 = 0; } while(0)

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    GPIO and peripheral I/O initialization
 * @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize(void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);

#endif // PIN_MANAGER_H
/**
 End of File
 */