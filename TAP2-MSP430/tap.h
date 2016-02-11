/*
 * tap.h
 *
 *  Created on: Feb 2, 2016
 *      Author: Bill
 */

#ifndef TAP_H_
#define TAP_H_

//*********** Set maximum LED ON time ******************************************
#define MAX_DELAY   63      // Set too large - get flicker
#define NUM_LEVELS  64      // Set too low - get more overhead and lose dynamic
                            //  range of intensity
                            // Powers of 2 are more efficient scaling from 0..FF

//*********** Map columns to hardware ******************************************
#define	COL0R_ON	P3OUT |= BIT1
#define	COL0R_OFF	P3OUT &= ~BIT1

#define	COL0G_ON	P4OUT |= BIT1
#define	COL0G_OFF	P4OUT &= ~BIT1

#define	COL0B_ON	P1OUT |= BIT6
#define	COL0B_OFF	P1OUT &= ~BIT6

#define	COL1R_ON	P4OUT |= BIT0
#define	COL1R_OFF	P4OUT &= ~BIT0

#define	COL1G_ON	P4OUT |= BIT2
#define	COL1G_OFF	P4OUT &= ~BIT2

#define	COL1B_ON	P1OUT |= BIT7
#define	COL1B_OFF	P1OUT &= ~BIT7

#define	COL2R_ON	P4OUT |= BIT3
#define	COL2R_OFF	P4OUT &= ~BIT3

#define	COL2G_ON	P4OUT |= BIT7
#define	COL2G_OFF	P4OUT &= ~BIT7

#define	COL2B_ON	P4OUT |= BIT6
#define	COL2B_OFF	P4OUT &= ~BIT6

#define	COL3R_ON	P3OUT |= BIT0
#define	COL3R_OFF	P3OUT &= ~BIT0

#define	COL3G_ON	P3OUT |= BIT2
#define	COL3G_OFF	P3OUT &= ~BIT2

#define	COL3B_ON	P1OUT |= BIT5
#define	COL3B_OFF	P1OUT &= ~BIT5

#define	COL4R_ON	P1OUT |= BIT4
#define	COL4R_OFF	P1OUT &= ~BIT4

#define	COL4G_ON	P1OUT |= BIT2
#define	COL4G_OFF	P1OUT &= ~BIT2

#define	COL4B_ON	P1OUT |= BIT3
#define	COL4B_OFF	P1OUT &= ~BIT3

#define	COL5R_ON	P5OUT |= BIT0
#define	COL5R_OFF	P5OUT &= ~BIT0

#define	COL5G_ON	P6OUT |= BIT7
#define	COL5G_OFF	P6OUT &= ~BIT7

#define	COL5B_ON	P6OUT |= BIT6
#define	COL5B_OFF	P6OUT &= ~BIT6

#define	COL6R_ON	P6OUT |= BIT0
#define	COL6R_OFF	P6OUT &= ~BIT0

#define	COL6G_ON	P6OUT |= BIT5
#define	COL6G_OFF	P6OUT &= ~BIT5

#define	COL6B_ON	P6OUT |= BIT4
#define	COL6B_OFF	P6OUT &= ~BIT4

#define	COL7R_ON	P6OUT |= BIT1
#define	COL7R_OFF	P6OUT &= ~BIT1

#define	COL7G_ON	P5OUT |= BIT1
#define	COL7G_OFF	P5OUT &= ~BIT1

#define	COL7B_ON	P6OUT |= BIT3
#define	COL7B_OFF	P6OUT &= ~BIT3

#endif /* TAP_H_ */
