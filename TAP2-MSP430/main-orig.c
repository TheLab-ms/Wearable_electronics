#include <msp430.h> 

//*********** EXTERNAL VARIABLES ***********************************************
extern const unsigned char font_basic[ ][8];

//********  Globals  *************************************************************************
//#define BLUELEDDELAY 700
//#define REDLEDDELAY 700
//#define GREENLEDDELAY 700
#define MAXDELAY 600
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


//****************************************************************************************************
int main(void)
{
	volatile unsigned int i, loops;
	volatile unsigned char next_color;

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


//    loops=0;
//      while(1)
//      {
//    	loops++;
//    	if(loops>200)
//    	{
//    		loops=0;
//    		next_color++;
//    		if(next_color > 3) next_color=0;
//    		set_full_array_color(next_color);
//
//    	}
//
//
//    	//pulse all LEDs once
//    	pulse_LEDs();
//
//        P6OUT ^= BIT2;                          // Toggle P6.2
//        //my_delay(6000);
//      }
//
//      return 0;

    unsigned char x, y;
    unsigned int offset;
    unsigned char charnext;

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

//*****************************************************************************************************
void all_off()
{
    //ALL OFF

}


//*****************************************************************************************************
void set_full_array_color(color_number)
{
	if(color_number == 0)//red
	{
		current_red_level = MAXDELAY;
		current_green_level = 10;
		current_blue_level = 10;
	}
	if(color_number == 1)//green
	{
		current_green_level = MAXDELAY;
		current_red_level = 10;
		current_blue_level = 10;
	}
	if(color_number == 2)//blue
	{
		current_blue_level = MAXDELAY;
		current_red_level = 10;
		current_green_level = 10;

	}
	if(color_number == 3)//white
	{
		current_red_level = MAXDELAY;
		current_green_level = MAXDELAY;
		current_blue_level = MAXDELAY;
	}

}


//*****************************************************************************************************
void pulse_LEDs()
{
	unsigned char x;

	//latch 0 into U5 B input - this will turn on power to first row
	PJOUT &= ~BIT3;//make B input low
	//clock U5
	PJOUT &= ~BIT0;
	PJOUT |= BIT0;

	//first row of LEDs now has power...

	PJOUT |= BIT3;//make B input on U5 high so the shift register clocks a single zero across to power each row


	//pulse all columns with required delay times and then power the next row
	for(x=0; x<8; x++)
	{

		P3OUT |= BIT1;
		my_delay(current_red_level);
		P3OUT &= ~BIT1;

		P4OUT |= BIT1;
		my_delay(current_green_level);
		P4OUT &= ~BIT1;

		P1OUT |= BIT6;
		my_delay(current_blue_level);
		P1OUT &= ~BIT6;

		P4OUT |= BIT0;
		my_delay(current_red_level);
		P4OUT &= ~BIT0;

		P4OUT |= BIT2;
		my_delay(current_green_level);
		P4OUT &= ~BIT2;

		P1OUT |= BIT7;
		my_delay(current_blue_level);
		P1OUT &= ~BIT7;

		P4OUT |= BIT3;
		my_delay(current_red_level);
		P4OUT &= ~BIT3;

		P4OUT |= BIT7;
		my_delay(current_green_level);
		P4OUT &= ~BIT7;

		P4OUT |= BIT6;
		my_delay(current_blue_level);
		P4OUT &= ~BIT6;

		P3OUT |= BIT0;
		my_delay(current_red_level);
		P3OUT &= ~BIT0;

		P3OUT |= BIT2;
		my_delay(current_green_level);
		P3OUT &= ~BIT2;

		P1OUT |= BIT5;
		my_delay(current_blue_level);
		P1OUT &= ~BIT5;

		P1OUT |= BIT4;
		my_delay(current_red_level);
		P1OUT &= ~BIT4;

		P1OUT |= BIT2;
		my_delay(current_green_level);
		P1OUT &= ~BIT2;

		P1OUT |= BIT3;
		my_delay(current_blue_level);
		P1OUT &= ~BIT3;

		P5OUT |= BIT0;
		my_delay(current_red_level);
		P5OUT &= ~BIT0;

		P6OUT |= BIT7;
		my_delay(current_green_level);
		P6OUT &= ~BIT7;

		P6OUT |= BIT6;
		my_delay(current_blue_level);
		P6OUT &= ~BIT6;

		P6OUT |= BIT0;
		my_delay(current_red_level);
		P6OUT &= ~BIT0;

		P6OUT |= BIT5;
		my_delay(current_green_level);
		P6OUT &= ~BIT5;

		P6OUT |= BIT4;
		my_delay(current_blue_level);
		P6OUT &= ~BIT4;

		P6OUT |= BIT1;
		my_delay(current_red_level);
		P6OUT &= ~BIT1;

		P5OUT |= BIT1;
		my_delay(current_green_level);
		P5OUT &= ~BIT1;

		P6OUT |= BIT3;
		my_delay(current_blue_level);
		P6OUT &= ~BIT3;

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
		__delay_cycles(1);
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


