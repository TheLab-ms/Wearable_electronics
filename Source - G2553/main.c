#include <msp430.h> 

extern const unsigned char font1[95][64];
extern const unsigned char font_basic[ ][8];

#define  BINARY 10
#define  ASCIIFONT1 11
#define  ASCIIFONT2 12
#define  HORIZLINELEFT 20
#define  HORIZLINERIGHT 21
#define  VERTLINEBOTTOM 22
#define  VERTLINETOP 23



//*******  GLOBALS  **********************************************************************************
unsigned char LED_data[265];
unsigned char redlevel;
unsigned char bluelevel;
unsigned char grnlevel;
volatile unsigned char intcount;
unsigned char rxbyte;
unsigned char data_index;
unsigned char current_red_level;
unsigned char current_blue_level;
unsigned char current_green_level;
unsigned char receiving_data;
volatile unsigned char myaddr;//changed JUNE18
//unsigned char first_serial_byte;
volatile unsigned char halt_update;
volatile unsigned char blank_display;


//*******  PROTOTYPES  *******************************************************************************
void us_delay(unsigned char dly);
void init_ports(void);
void init_LED_data(unsigned char data);
void init_uart(void);
void init_timer(void);
void init_system_clock(void);
void display_red_green_blue(void);
void display_LED_data(void);
void process_data_packet(void);
void init_i2c(void); //added JUNE18
void process_column(unsigned char index, unsigned char column_length);

//  G2
//  G2
//  G2
//  G2
//  G2

/*
//******************************************
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{
	rxbyte = UCA0RXBUF;//read byte
	first_serial_byte=1;

	if((rxbyte == 0) || (rxbyte == my_id))//if this is the start of a new data packet then init index
	{
		data_index=0;
		receiving_data=1;
	}

	LED_data[data_index++] = rxbyte; //save to the buffer

	if(rxbyte == 9)//full packet received
		receiving_data=0;
}
// while (!(IFG2&UCA0TXIFG));                // USCI_A0 TX buffer ready?
//  UCA0TXBUF = 0xAA;                    // TX -> RXed character
*/


/*
// USCI_B0 Data ISR
#pragma vector = USCIAB0TX_VECTOR
__interrupt void USCIAB0TX_ISR(void)
{
  UCB0TXBUF = TXData;                       // TX data
  //__bic_SR_register_on_exit(CPUOFF);        // Exit LPM0
}
*/


// USCI_B0 ISR - TX vector used for TX/RX interrupt, RX vector used for state interrupts!!!
#pragma vector = USCIAB0TX_VECTOR
__interrupt void USCIAB0TX_ISR(void)
{
	rxbyte = UCB0RXBUF;//read byte

	//first_serial_byte=1;//stop font set display

	if((rxbyte == 0) || (rxbyte == myaddr))//if this is the start of a new data packet then init index
	{
		data_index=0;
		halt_update=1;
	}

	if(halt_update==1)
		LED_data[data_index++] = rxbyte; //save to the buffer

	if(rxbyte == 9)//full packet received
	{
		process_data_packet();
		halt_update=0;
	}
}



//  G2
//  G2
//  G2
//  G2
//  G2

//****************************************************************************************************
//****************************************************************************************************
int main(void)
{
	unsigned int x;
	volatile unsigned char charsel, skip;


    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

    init_system_clock(); //16MHz DCO

    init_ports();
	//init_uart();
	init_i2c(); //call **after** init_ports()
	receiving_data=0;
	halt_update=0;
	data_index=0;
	//packet_started=0;
	blank_display=1;//start with display off


	//__bis_SR_register(LPM0_bits + GIE);       // Enter LPM0 w/ interrupt
	__bis_SR_register(GIE);                   // Enable global interrupts

	//while(1)
	display_red_green_blue();


	//these color levels will be set by every ASCII character request sent from the central processor
	current_red_level   = 0;   //red
	current_blue_level  = 0;   //blue
	current_green_level = 250; //green

	//two steps are required to make all LEDs turn off:
	for(x=0; x<260; x++)
		LED_data[x] = 0;//turn all LEDs off in this 8x8 segment
	P3OUT = 25;//all LEDs off by writing to dead/skip zone in the 8-bit counter


	skip=0;
	charsel=0;
	//first_serial_byte=0;
	//init_LED_data(charsel);
	while(1)
	{
		//******  ASCII character display DEMO ONLY - to be removed later  ***********
	/*
		if(first_serial_byte==0)
		{
			skip++;
			if(skip>250)
			{
				skip=0;
				init_LED_data(charsel++);//load next character in font set
				if(charsel>4) charsel=0;
			}
		}*/


		//strobe LEDs based on the data in the LED_data[] array
		display_LED_data();

	}

	return 0;
}




//****************************************************************************************************
void init_i2c()
{
	myaddr = P2IN;//read this MSP430's segment ID as defined by the termination of P2.0, P2.1 and P2.2
	myaddr &= 0x07;
//myaddr = 6;//for debug purposes

	P1DIR &= ~BIT7;//input
	P1DIR &= ~BIT6;//input
	P1SEL |= BIT6 + BIT7;                     // Assign I2C pins to USCI_B0
	P1SEL2|= BIT6 + BIT7;                     // Assign I2C pins to USCI_B0
	UCB0CTL1 |= UCSWRST;                      // Enable SW reset
	UCB0CTL0 = UCMODE_3 + UCSYNC;             // I2C Slave, synchronous mode
	UCB0I2COA = myaddr;                       // assign my **hardware** Address - logical address for interrupt routine is myaddr+1
	myaddr++;								  //increment so the interrupt routine has the correct id for incoming packets
	UCB0CTL1 &= ~UCSWRST;                     // Clear SW reset, resume operation
	IE2 |= UCB0RXIE;                          // Enable RX interrupt
}


//***********************************************************************************************
void process_data_packet()
{
	volatile unsigned int x, lindex, segment_mode, offset;
	volatile unsigned char c1, c2, c3, c4, c5, c6, c7, c8, f1, f2;

	//determine if this is a ASCII characrter request or a binary image bitmap
	//load LED_data[] accordingly

	//byte 1:    Mode: 10=binary, 11=font1, 12=font2, etc, 20=Horizontal Top Line , 21=Vertical Left Line , etc.
	if(LED_data[1] == 10)
		segment_mode = BINARY;
	if(LED_data[1] == 11)
		segment_mode = ASCIIFONT1;
	if(LED_data[1] == 12)
		segment_mode = ASCIIFONT2;
	if(LED_data[1] == 20)
		segment_mode = HORIZLINELEFT;
	if(LED_data[1] == 21)
		segment_mode = HORIZLINERIGHT;
	if(LED_data[1] == 22)
		segment_mode = VERTLINEBOTTOM;
	if(LED_data[1] == 23)
		segment_mode = VERTLINETOP;

	//byte 2:    Red Color Level  (10-255) For >= ASCII mode only.
	current_red_level = (LED_data[2]-10); //if 10 was sent from host then need zero in LED_data[1] to make sure LED is fully off

	//byte 3:    Blue Color Level  (10-255) For >= ASCII mode only.
	current_blue_level = (LED_data[3]-10); //if 10 was sent from host then need zero in LED_data[1] to make sure LED is fully off

	//byte 4:    Green Color Level  (10-255) For >= ASCII mode only.
	current_green_level = (LED_data[4]-10); //if 10 was sent from host then need zero in LED_data[1] to make sure LED is fully off


	if(segment_mode == BINARY)
	{
		blank_display=0;//display on
		//byte 5:    First byte of data. Single byte if ASCII, 255 if binary. All bytes must be 10-255.
		lindex=5;
		for(x=0; x<0xFF; x++)
			LED_data[x] = LED_data[lindex++]-10; //subtract 10 to get to a delay of zero so can fully turn off the LED
	}

	if(segment_mode == ASCIIFONT1)
	{
		blank_display=0;//display on
		init_LED_data(LED_data[5]-31);//load selected character in font set
	}

	if(segment_mode == ASCIIFONT2)
	{
		blank_display=0;//display on
		f1 = LED_data[5]-10;
		f2 = LED_data[6]-10;
		offset = LED_data[7]-10;
		init_font_LED_data(f1, f2, offset);
	}

	if(segment_mode == VERTLINEBOTTOM)
	{
		blank_display=0;//display on

		c1 = LED_data[5]-10;
		c2 = LED_data[6]-10;
		c3 = LED_data[7]-10;
		c4 = LED_data[8]-10;
		c5 = LED_data[9]-10;
		c6 = LED_data[10]-10;
		c7 = LED_data[11]-10;
		c8 = LED_data[12]-10;

		process_column(224, c1);//starting address for base LED in column 1, number of LEDs in this column to turn on
		process_column(227, c2);//column 2
		process_column(230, c3);//column 3
		process_column(233, c4);//column 4
		process_column(236, c5);//column 5
		process_column(239, c6);//column 6
		process_column(242, c7);//column 7
		process_column(245, c8);//column 8
	}
}


//for(x=0; x<260; x++)
//	LED_data[x] = 0;//turn all LEDs off in this 8x8 segment


//***********************************************************************************************
void process_column(unsigned char index, unsigned char column_length)
{
	volatile unsigned char x, len;

	//index is the starting address for base LED in desired column

	len = column_length;

	if(len<9)//if desired column height > 0, process this column - skip otherwise
	{
		for(x=0;  x<len; x++)
		{
			LED_data[index++] = current_red_level;
			LED_data[index++] = current_blue_level;
			LED_data[index] = current_green_level;
			index-=34;
		}

		len++;

		for(x=len; x<9; x++)//blank out rest of column
		{
			LED_data[index++] = 0;
			LED_data[index++] = 0;
			LED_data[index] = 0;
			index-=34;
		}


	}
}




//***********************************************************************************************
void us_delay(unsigned char dly)
{
	volatile unsigned char x;
	dly>>=2;//divide by 2
	for(x=0; x<dly; x++)
			x=x;
}


//****************************************************************************************************
void init_LED_data(unsigned char data)
{
	unsigned int x;
	unsigned char index;

	index=0;
	for(x=0; x<255; x+=3)
	{
		if((x & 0x18) == 0x18)//skip over P3 and P4 equal "11" state
			x+=8;

		LED_data[x]   = font1[data][index] * current_red_level;//red
		LED_data[x+1] = font1[data][index] * current_blue_level;//blue
		LED_data[x+2] = font1[data][index++] * current_green_level;//green
	}
}

//****************************************************************************************************
void init_font_LED_data(unsigned char ctxt, unsigned char cnext, unsigned int offset)
{
	unsigned int h, i, j;
	const unsigned char mask = 1;
	volatile unsigned int tempbit = 0;

	h =0;

	// Loops Through Each Byte in both the ctxt and cnext arrays
	for( j = 0; j < 8; j++)
	{
		// Loops Through Each Bit in each Byte in data array
		for ( i = 0; i < 8; i++ )
		{
			if ( i >= offset ) {  // Skips bits of offset value to be filled in with cnext array for scrolling text
				if((h & 0x18) == 0x18) { h+=8; } //skip over P3 and P4 equal "11" state
				tempbit   = (font_basic[ctxt][j] & ( mask << i ) ) != 0;
				LED_data[h] = tempbit * current_red_level;
				LED_data[h+1] = tempbit * current_blue_level;
				LED_data[h+2] = tempbit * current_green_level;
				h+=3;
			}
		}

		if (offset >= 1) {  // Only do this second loop if needed
			// Loops Through Each Bit in each Byte in datanext array
			for ( i = 0; i < 8; i++ )
			{
				if ( offset > i ) {  // Fills in the bits skipped in the first byte with bits from the next byte
					if((h & 0x18) == 0x18) { h+=8; } //skip over P3 and P4 equal "11" state
					tempbit   = (font_basic[cnext][j] & ( mask << i ) ) != 0;
					LED_data[h] = tempbit * current_red_level;
					LED_data[h+1] = tempbit * current_blue_level;
					LED_data[h+2] = tempbit * current_green_level;
					h+=3;
				}
			}
		}

	}

}

//****************************************************************************************************
void init_system_clock()
{
	if (CALBC1_16MHZ==0xFF)					// If calibration constant erased
	{
		while(1);                               // do not load, trap CPU!!
	}

	DCOCTL = 0;                               // Select lowest DCOx and MODx settings
	BCSCTL1 = CALBC1_16MHZ;                    // Set DCO to 8MHz
	DCOCTL = CALDCO_16MHZ;
}

//****************************************************************************************************
void display_LED_data()
{
	unsigned int x;

	//strobe LEDs based on the data in the LED_data[] array
	for(x=0; x<255; x+=3)
	{

		if(blank_display==1)
		{
			P3OUT = 25;//all LEDs off by writing to dead/skip zone in the 8-bit counter
			continue;
		}

		if((x & 0x18) == 0x18)//skip over P3 and P4 equal "11" state
			x+=8;

		while(halt_update==1);

		int delay1, delay2, delay3;
		//*** If LED is completley off we still need a minimum delay for consistency
		if ((LED_data[x] == 0) && (LED_data[x+1] == 0) && (LED_data[x+2] == 0)) {
			delay1 = 50;
		    delay2 = 50;
		    delay3 = 50;
		} else {
			delay1 = LED_data[x];
			delay2 = LED_data[x+1];
			delay3 = LED_data[x+2];
		}

		while(halt_update==1);

		if(LED_data[x])//if data > zero
			P3OUT = x;
		us_delay(delay1);
		P3OUT = 25;//all LEDs off by writing to dead/skip zone in the 8-bit counter

		while(halt_update==1);

		if(LED_data[x+1])
			P3OUT = x+1;
		us_delay(delay2);
		P3OUT = 25;//all LEDs off by writing to dead/skip zone in the 8-bit counter

		while(halt_update==1);

		if(LED_data[x+2])
			P3OUT = x+2;
		us_delay(delay3);
		P3OUT = 25;//all LEDs off by writing to dead/skip zone in the 8-bit counter

		while(halt_update==1);

	}
}



/*
//****************************************************************************************************
void init_uart()
{
	UCA0CTL1 |= UCSSEL_2;                     // SMCLK

	UCA0BR0 = 138;                              // 115200
	UCA0BR1 = 0;                              // 115200
	UCA0MCTL = UCBRS2 + UCBRS0;               // Modulation UCBRSx = 5

	UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**

	IE2 |= UCA0RXIE;                          // Enable USCI_A0 RX interrupt
}
*/





//****************************************************************************************************
void init_ports()
{
	//8-bit parallel output port
	P3OUT = 0;
	P3DIR = 0xFF;//all output

	//port 1
	P1OUT &= BIT0;//not used, make output low
	P1OUT &= BIT3;//not used, make output low
	P1OUT &= BIT4;//not used, make output low
	P1OUT &= BIT5;//not used, make output low
	P1DIR |= BIT0;
	P1DIR |= BIT3;
	P1DIR |= BIT4;
	P1DIR |= BIT5;

	P1DIR &= ~BIT6;//I2C input
	P1DIR &= ~BIT7;//I2C input

	//P1DIR &= ~BIT1;//UART receive RXD
	P1SEL |= BIT1;//select UART function
	P1SEL2 |= BIT1;//select UART function

	//P1DIR |= BIT2;//UART transmit TXD
	P1SEL |= BIT2;//select UART function
	P1SEL2 |= BIT2;//select UART function

	P2DIR &= ~BIT0;//Segment ID LSbit
	P2DIR &= ~BIT1;
	P2DIR &= ~BIT2;//Segment ID MSbit

	//unused
	P2OUT &= BIT3;//not used, make output low
	P2OUT &= BIT4;
	P2OUT &= BIT5;
	P2OUT &= BIT6;
	P2OUT &= BIT7;
	P2DIR |= BIT3;
	P2DIR |= BIT4;
	P2DIR |= BIT5;
	P2DIR |= BIT6;
	P2DIR |= BIT7;
}





//****************************************************************************************************
void display_red_green_blue()
{
	unsigned int x, y;


  redlevel=255;
  bluelevel=0;
  grnlevel=0;
	for(y=0; y<200; y++)
	{
		for(x=0; x<0xFF; x+=3)
		{
			if((x & 0x18) == 0x18)//skip over P3 and P4 equal "11" state
				x+=8;

			P3OUT = x;
			us_delay(redlevel);
			P3OUT = x+1;
			us_delay(bluelevel);
			P3OUT = x+2;
			us_delay(grnlevel);
		}
	}


	  redlevel=0;
	  bluelevel=0;
	  grnlevel=255;
		for(y=0; y<200; y++)
		{
			for(x=0; x<0xFF; x+=3)
			{
				if((x & 0x18) == 0x18)//skip over P3 and P4 equal "11" state
					x+=8;

				P3OUT = x;
				us_delay(redlevel);
				P3OUT = x+1;
				us_delay(bluelevel);
				P3OUT = x+2;
				us_delay(grnlevel);
			}
		}




		  redlevel=0;
		  bluelevel=255;
		  grnlevel=0;
			for(y=0; y<200; y++)
			{
				for(x=0; x<0xFF; x+=3)
				{
					if((x & 0x18) == 0x18)//skip over P3 and P4 equal "11" state
						x+=8;

					P3OUT = x;
					us_delay(redlevel);
					P3OUT = x+1;
					us_delay(bluelevel);
					P3OUT = x+2;
					us_delay(grnlevel);
				}
			}
}










/*  CODE GRAVEYARD

//****************************************************************************************************
void init_LED_data()
{
	unsigned int x;

	for(x=0; x<0xFF; x+=3)
	{
		if((x & 0x18) == 0x18)//skip over P3 and P4 equal "11" state
			x+=8;

		LED_data[x] = redlevel;//red
		LED_data[x+1] = bluelevel;//blue
		LED_data[x+2] = grnlevel;//green
	}
}*/




/*
	startbtn = P2IN;
	startbtn &= BIT6;

	while(startbtn==0)
	{
		spinner();
		startbtn = P2IN;
		startbtn &= BIT6;
	}


	//serial_number = DetectSensor();
    allow_update=0;
	//fdata = ReadTempSensor();
	fdata = measure_volts();
	fdata = 0.08;
    ftoa(fdata,str,3);//convert to string
    allow_update=1;
    us_delay(150000);


	  //if this interrupt occurrs 5 times then its time to update the display
//	  int_count++;
//	  if(int_count>2)
//	  {
//		  int_count=0;
//		  if(allow_update==1)
//			  update_display(); //takes ~18mS
//	  }

*/


/*

init_timer();//used by color show to slowly change colors



//****************************************************************************************************
void init_timer()
{
	intcount=0;
	CCTL0 = CCIE;                             // CCR0 interrupt enabled/
	TACTL = TASSEL_2 + MC_2;                  // SMCLK, contmode      Period: 33uS
}



//This timer is started after power up for the light show start_color_show(); but terminated upon receipt of the first byte from the host.
//From that point forward, incoming packets from the host determine what is displayed.
//****************************************************************************************************
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
	  CCR0 -= 10;     // timer interval: 4.1mS


	  intcount++;
	  if(intcount>1)
	  {
		  intcount=0;

		  if(red_dir)//if direction is up...
			  redlevel+=2; //increase time red is on
		  else
			  redlevel-=2; //decrease
		  if(redlevel>253) red_dir=0; //if at top of brightness scale then change direction to down
		  if(redlevel<2)   red_dir=1; //if at bottom of brightness scale then change direction to up


		  if(blue_dir)
			  bluelevel++;
		  else
			  bluelevel--;
		  if(bluelevel>254) blue_dir=0;
		  if(bluelevel<1)   blue_dir=1;


		  if(grn_dir)
			  grnlevel+=1;
		  else
			  grnlevel-=1;
		  if(grnlevel>254) grn_dir=0;
		  if(grnlevel<1)   grn_dir=1;
	  }
}
*/
