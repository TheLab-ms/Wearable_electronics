#include <msp430.h>
#include "tap.h"

//********  Globals  *************************************************************************
unsigned char   *display_addr;
unsigned char   *display_ptr;
unsigned char   display_buffer[192];
volatile unsigned int	loops;

//#define BLUELEDDELAY 700
//#define REDLEDDELAY 700
//#define GREENLEDDELAY 700
#define MAXDELAY	MAX_DELAY
unsigned int current_red_level;
unsigned int current_green_level;
unsigned int current_blue_level;

//********  Prototypes  *************************************************************************
void SetVcoreUp (unsigned int level);
void init_ioports(void);
void init_clock(void);
void pulse_LEDs(void);
void my_delay(unsigned int x);
void initU5(void);


//*********** For demo *********************************************************
#include "demo.h"

//****************************************************************************************************
// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
	loops++;
	P1IFG &= ~BIT0; // P1.0 IFG cleared
}

//****************************************************************************************************
int main(void)
{
	volatile unsigned int i;
	volatile unsigned char next_color;
	unsigned char	x;

    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

    //PMAPPWD = 0x02D52;                        // Enable Write-access to modify port mapping registers
    //P4MAP7 = PM_MCLK;
    //PMAPPWD = 0;                              // Disable Write-Access to modify port mapping registers

    init_clock();
    init_ioports();
    initU5();//all 8 outputs high

    //P1DIR |= BIT0;                            // ACLK set out to pins
    //P1SEL |= BIT0;
    //P2DIR |= BIT2;                            // SMCLK set out to pins
    //P2SEL |= BIT2;
    //P4DIR |= BIT7;                            // MCLK set out to pins
    //P4SEL |= BIT7;

    for (x = 0; x < 192; x++)
    	display_buffer[x] = 0;

    display_addr = display_buffer;

    // Enable interrupt on port 1 pin 0
//    P1IE |= BIT0; // P1.0 interrupt enabled
//    P1IES |= BIT0; // P1.0 Hi/lo edge
//    P1IFG &= ~BIT0; // P1.0 IFG cleared
//	__bis_SR_register(GIE);                   // Enable global interrupts

#ifdef DEMO
    init_demo();
#endif

    loops=0;
      while(1)
      {
//    	loops++;

#ifdef DEMO
        if (scan == 0)
            {
            step_demo();

            scan = num_cycles;
            }
        scan--;
#endif

#if 0
    	if(loops>0)
    	{
    		loops=0;
    		next_color++;
    		if(next_color > 3) next_color=0;
    		set_full_array_color(next_color);

    	}
#endif

    	//pulse all LEDs once
    	pulse_LEDs();

        P6OUT ^= BIT2;                          // Toggle P6.2
        //my_delay(6000);
      }

      return 0;
}


//*****************************************************************************************************
void set_full_array_color(color_number)
{
	unsigned int	x;

	if(color_number == 0)//red
		{
		for (x = 0; x < 192; x = x + 3)
			{
			display_buffer[x] = MAXDELAY;
			display_buffer[x + 1] = 0;
			display_buffer[x + 2] = 0;
			}
		current_red_level = MAXDELAY;
		current_green_level = 10;
		current_blue_level = 10;
		}
	if(color_number == 1)//green
		{
		for (x = 0; x < 192; x = x + 3)
			{
			display_buffer[x] = 0;
			display_buffer[x + 1] = MAXDELAY;
			display_buffer[x + 2] = 0;
			}
		current_green_level = MAXDELAY;
		current_red_level = 10;
		current_blue_level = 10;
		}
	if(color_number == 2)//yellow
		{
		for (x = 0; x < 192; x = x + 3)
			{
			display_buffer[x] = 0;
			display_buffer[x + 1] = 0;
			display_buffer[x + 2] = MAXDELAY;
			}
		current_blue_level = 10;
		current_red_level = MAXDELAY;
		current_green_level = MAXDELAY;

		}
	if(color_number == 3)//white
		{
		for (x = 0; x < 192; x = x + 3)
			{
			display_buffer[x] = MAXDELAY;
			display_buffer[x + 1] = MAXDELAY;
			display_buffer[x + 2] = MAXDELAY;
			}
		current_red_level = MAXDELAY;
		current_green_level = MAXDELAY;
		current_blue_level = MAXDELAY;
		}
}


//*****************************************************************************************************
#define SCAN_COLUMN(TURN_COLUMN_ON,TURN_COLUMN_OFF) \
    { \
    delay = *display_ptr++; \
    if (delay != 0) \
        { \
        TURN_COLUMN_ON; \
        my_delay(delay); \
        TURN_COLUMN_OFF; \
        } \
    if (delay < MAX_DELAY) \
        my_delay(MAX_DELAY - delay); \
    }
void pulse_LEDs()
{
	unsigned char	delay;
	unsigned char	x;

	//latch 0 into U5 B input - this will turn on power to first row
	PJOUT &= ~BIT3;//make B input low
	//clock U5
	PJOUT &= ~BIT0;
	PJOUT |= BIT0;

	//first row of LEDs now has power...

	PJOUT |= BIT3;//make B input on U5 high so the shift register clocks a single zero across to power each row

	display_ptr = display_addr;

	//pulse all columns with required delay times and then power the next row
	for(x=0; x<8; x++)
	{

		SCAN_COLUMN(COL0R_ON, COL0R_OFF);
		SCAN_COLUMN(COL0G_ON, COL0G_OFF);
		SCAN_COLUMN(COL0B_ON, COL0B_OFF);

		SCAN_COLUMN(COL1R_ON, COL1R_OFF);
		SCAN_COLUMN(COL1G_ON, COL1G_OFF);
		SCAN_COLUMN(COL1B_ON, COL1B_OFF);

		SCAN_COLUMN(COL2R_ON, COL2R_OFF);
		SCAN_COLUMN(COL2G_ON, COL2G_OFF);
		SCAN_COLUMN(COL2B_ON, COL2B_OFF);

		SCAN_COLUMN(COL3R_ON, COL3R_OFF);
		SCAN_COLUMN(COL3G_ON, COL3G_OFF);
		SCAN_COLUMN(COL3B_ON, COL3B_OFF);

		SCAN_COLUMN(COL4R_ON, COL4R_OFF);
		SCAN_COLUMN(COL4G_ON, COL4G_OFF);
		SCAN_COLUMN(COL4B_ON, COL4B_OFF);

		SCAN_COLUMN(COL5R_ON, COL5R_OFF);
		SCAN_COLUMN(COL5G_ON, COL5G_OFF);
		SCAN_COLUMN(COL5B_ON, COL5B_OFF);

		SCAN_COLUMN(COL6R_ON, COL6R_OFF);
		SCAN_COLUMN(COL6G_ON, COL6G_OFF);
		SCAN_COLUMN(COL6B_ON, COL6B_OFF);

		SCAN_COLUMN(COL7R_ON, COL7R_OFF);
		SCAN_COLUMN(COL7G_ON, COL7G_OFF);
		SCAN_COLUMN(COL7B_ON, COL7B_OFF);

		//enable power to next row of LEDs
		//clock U5 moving the zero across the shift register
		PJOUT &= ~BIT0;
		PJOUT |= BIT0;
	}
}


//*****************************************************************************************************
void init_clock()
{
    // Increase Vcore setting to level3 to support fsystem=25MHz
      // NOTE: Change core voltage one level at a time..
      SetVcoreUp (0x01);
      SetVcoreUp (0x02);
      SetVcoreUp (0x03);

      UCSCTL3 = SELREF_2;                       // Set DCO FLL reference = REFO
      UCSCTL4 |= SELA_2;                        // Set ACLK = REFO

      __bis_SR_register(SCG0);                  // Disable the FLL control loop
      UCSCTL0 = 0x0000;                         // Set lowest possible DCOx, MODx
      UCSCTL1 = DCORSEL_7;                      // Select DCO range 50MHz operation
      UCSCTL2 = FLLD_1 + 762;                   // Set DCO Multiplier for 25MHz
                                                // (N + 1) * FLLRef = Fdco
                                                // (762 + 1) * 32768 = 25MHz
                                                // Set FLL Div = fDCOCLK/2
      __bic_SR_register(SCG0);                  // Enable the FLL control loop

      // Worst-case settling time for the DCO when the DCO range bits have been
      // changed is n x 32 x 32 x f_MCLK / f_FLL_reference. See UCS chapter in 5xx
      // UG for optimization.
      // 32 x 32 x 25 MHz / 32,768 Hz ~ 780k MCLK cycles for DCO to settle
      __delay_cycles(782000);

      // Loop until XT1,XT2 & DCO stabilizes - In this case only DCO has to stabilize
      do
      {
        UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + DCOFFG);
                                                // Clear XT2,XT1,DCO fault flags
        SFRIFG1 &= ~OFIFG;                      // Clear fault flags
      }while (SFRIFG1&OFIFG);                   // Test oscillator fault flag
}




//*****************************************************************************************************
void my_delay(unsigned int x)
{
	while(x--)
		__delay_cycles(10);
}


//*****************************************************************************************************
void initU5()
{
	unsigned char x;

	//reset U5 to all outputs low - bad! - all LED rows powered!
	//PJOUT &= ~BIT2;//reset low
	//PJOUT |= BIT2;//reset high

	PJOUT |= BIT3;//make B input of U5 high

	//clock all 1s into U5 to turn all ROWS off
	for(x=0; x<8; x++)
	{
		PJOUT &= ~BIT0;
		PJOUT |= BIT0;
	}
}





//*****************************************************************************************************
void init_ioports()
{

	PJDIR |= BIT3;
	PJOUT |= BIT2;
	PJDIR |= BIT2;
	PJDIR |= BIT0;

	P3DIR |= BIT1;
	P3OUT &= ~BIT1;
	P4DIR |= BIT1;
	P4OUT &= ~BIT1;
	P1DIR |= BIT6;
	P1OUT &= ~BIT6;

	P4DIR |= BIT0;
	P4OUT &= ~BIT0;
	P4DIR |= BIT2;
	P4OUT &= ~BIT2;
	P1DIR |= BIT7;
	P1OUT &= ~BIT7;

	P4DIR |= BIT3;
	P4OUT &= ~BIT3;
	P4DIR |= BIT7;
	P4OUT &= ~BIT7;
	P4DIR |= BIT6;
	P4OUT &= ~BIT6;

	P3DIR |= BIT0;
	P3OUT &= ~BIT0;
	P3DIR |= BIT2;
	P3OUT &= ~BIT2;
	P1DIR |= BIT5;
	P1OUT &= ~BIT5;

	P1DIR |= BIT4;
	P1OUT &= ~BIT4;
	P1DIR |= BIT2;
	P1OUT &= ~BIT2;
	P1DIR |= BIT3;
	P1OUT &= ~BIT3;

	P5DIR |= BIT0;
	P5OUT &= ~BIT0;
	P6DIR |= BIT7;
	P6OUT &= ~BIT7;
	P6DIR |= BIT6;
	P6OUT &= ~BIT6;

	P6DIR |= BIT0;
	P6OUT &= ~BIT0;
	P6DIR |= BIT5;
	P6OUT &= ~BIT5;
	P6DIR |= BIT4;
	P6OUT &= ~BIT4;

	P6DIR |= BIT1;
	P6OUT &= ~BIT1;
	P5DIR |= BIT1;
	P5OUT &= ~BIT1;
	P6DIR |= BIT3;
	P6OUT &= ~BIT3;


	//test point
	P6DIR |= BIT2;//

}


void SetVcoreUp (unsigned int level)
{
	//PROVIDED BY TI EXAMPLE CODE...

  // Open PMM registers for write
  PMMCTL0_H = PMMPW_H;
  // Set SVS/SVM high side new level
  SVSMHCTL = SVSHE + SVSHRVL0 * level + SVMHE + SVSMHRRL0 * level;
  // Set SVM low side to new level
  SVSMLCTL = SVSLE + SVMLE + SVSMLRRL0 * level;
  // Wait till SVM is settled
  while ((PMMIFG & SVSMLDLYIFG) == 0);
  // Clear already set flags
  PMMIFG &= ~(SVMLVLRIFG + SVMLIFG);
  // Set VCore to new level
  PMMCTL0_L = PMMCOREV0 * level;
  // Wait till new level reached
  if ((PMMIFG & SVMLIFG))
    while ((PMMIFG & SVMLVLRIFG) == 0);
  // Set SVS/SVM low side to new level
  SVSMLCTL = SVSLE + SVSLRVL0 * level + SVMLE + SVSMLRRL0 * level;
  // Lock PMM registers for write access
  PMMCTL0_H = 0x00;
}