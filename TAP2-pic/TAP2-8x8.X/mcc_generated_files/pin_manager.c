/**
  Generated Pin Manager File

  Company:
    Microchip Technology Inc.

  File Name:
    pin_manager.c

  Summary:
    This is the Pin Manager file generated using MPLAB® Code Configurator

  Description:
    This header file provides implementations for pin APIs for all pins selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB® Code Configurator - v2.25.2
        Device            :  PIC16F1947
        Driver Version    :  1.02
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

#include <xc.h>
#include "pin_manager.h"

void PIN_MANAGER_Initialize(void) {
    LATA = 0x00;
    TRISA = 0xFF;
    ANSELA = 0x00;

    LATB = 0x02;
    TRISB = 0x01;
    WPUB = 0x00;

    LATC = 0x00;
    TRISC = 0xFD;

    LATD = 0xFE;
    TRISD = 0x00;

    LATE = 0xFF;
    TRISE = 0x00;
    ANSELE = 0x00;

    LATF = 0xFF;
    TRISF = 0x00;
    ANSELF = 0x00;

    LATG = 0x00;
    TRISG = 0x3F;
    ANSELG = 0x18;
    WPUG = 0x00;

    OPTION_REGbits.nWPUEN = 0x01;

    APFCON = 0x00;

    // enable interrupt-on-change individually    
    IOCBN0 = 1;

    // enable interrupt-on-change globally
    INTCONbits.IOCIE = 1;

}

void PIN_MANAGER_IOC(void) {
    if ((IOCBN0 == 1) && (IOCBF0 == 1)) {
        //@TODO Add handling code for IOC on pin RB0

        // clear interrupt-on-change flag
        IOCBF0 = 0;
    }
}
/**
 End of File
 */