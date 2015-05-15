#include <msp430.h> 

extern const unsigned char font1[95][64];



#define  BINARY 10
#define  ASCIIFONT1 11
#define  ASCIIFONT2 12
#define  ASCIIHORIZTOPLINE 20
#define  ASCIIVERTLEFTLINE  21



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
volatile unsigned char my_id;
unsigned char first_serial_byte;



//*******  PROTOTYPES  *******************************************************************************
void us_delay(unsigned char dly);
void init_ports(void);
void init_LED_data(unsigned char data);
void init_uart(void);
void init_timer(void);
void init_system_clock(void);
void display_red_green_blue(void);
void process_data_packet(void);




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

//transmit test code for testing baud rate (115200)
//while(1)
//{
// while (!(IFG2&UCA0TXIFG));                // USCI_A0 TX buffer ready?
//  UCA0TXBUF = 0xAA;                    // TX -> RXed character
//}




//****************************************************************************************************
//****************************************************************************************************
int main(void)
{
	unsigned int x;
	volatile unsigned char charsel, skip;


    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

    init_system_clock(); //16MHz DCO
	init_ports();
	init_uart();
	//__bis_SR_register(LPM0_bits + GIE);       // Enter LPM0 w/ interrupt
	__bis_SR_register(GIE);                   // Enable global interrupts



	//while(1)
	display_red_green_blue();

	my_id = P2IN;//read this MSP430's segment ID as defined by the termination of P2.0, P2.1 and P2.2
	my_id &= 0x07;
my_id = 1;//for debug purposes



	//these color levels will be set by every ASCII character request sent from the central processor
	current_red_level   = 0;   //red
	current_blue_level  = 0;   //blue
	current_green_level = 200; //green


	skip=0;
	charsel=0;
	first_serial_byte=0;
	init_LED_data(charsel);
	while(1)//this loop displays all desired data
	{
		if(receiving_data==1)//wait here while receiving a packet
		{
			while(receiving_data==1);//wait until all bytes received

			//packet just received is either an ASCII character request or a binary image packet - process accordingly
			process_data_packet();
		}



		//******  ASCII character display DEMO ONLY - to be removed later  ***********
		if(first_serial_byte==0)
		{
			skip++;
			if(skip>250)
			{
				skip=0;
				init_LED_data(charsel++);//load next character in font set
				if(charsel>4) charsel=0;
			}
		}
		//******************************************


		//strobe LEDs based on the data in the LED_data[] array
		for(x=0; x<255; x+=3)
		{
			if(receiving_data==1)
				x=300;//terminate update

			if((x & 0x18) == 0x18)//skip over P3 and P4 equal "11" state
				x+=8;

			if(LED_data[x])//if data > zero
				P3OUT = x;
			us_delay(LED_data[x]);

			if(LED_data[x+1])
				P3OUT = x+1;
			us_delay(LED_data[x+1]);

			if(LED_data[x+2])
				P3OUT = x+2;
			us_delay(LED_data[x+2]);
		}
	}

	return 0;
}





//***********************************************************************************************
void process_data_packet()
{
	unsigned int x, lindex, segment_mode;
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
		segment_mode = ASCIIHORIZTOPLINE;
	if(LED_data[1] == 21)
		segment_mode = ASCIIVERTLEFTLINE;

	//byte 2:    Red Color Level  (10-255) For >= ASCII mode only.
	current_red_level = (LED_data[2]-10); //if 10 was sent from host then need zero in LED_data[1] to make sure LED is fully off

	//byte 3:    Blue Color Level  (10-255) For >= ASCII mode only.
	current_blue_level = (LED_data[3]-10); //if 10 was sent from host then need zero in LED_data[1] to make sure LED is fully off

	//byte 4:    Green Color Level  (10-255) For >= ASCII mode only.
	current_green_level = (LED_data[4]-10); //if 10 was sent from host then need zero in LED_data[1] to make sure LED is fully off


	if(segment_mode == BINARY)
	{
		//byte 5:    First byte of data. Single byte if ASCII, 255 if binary. All bytes must be 10-255.
		lindex=5;
		for(x=0; x<0xFF; x++)
			LED_data[x] = LED_data[lindex++]-10; //subtract 10 to get to a delay of zero so can fully turn off the LED
	}

	if(segment_mode == ASCIIFONT1)
		init_LED_data(LED_data[5]-31);//load selected character in font set
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
void init_uart()
{
	UCA0CTL1 |= UCSSEL_2;                     // SMCLK

	UCA0BR0 = 138;                              // 115200
	UCA0BR1 = 0;                              // 115200
	UCA0MCTL = UCBRS2 + UCBRS0;               // Modulation UCBRSx = 5

	UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**

	IE2 |= UCA0RXIE;                          // Enable USCI_A0 RX interrupt
}






//****************************************************************************************************
void init_ports()
{
	//primary output port
	P3OUT = 0;
	P3DIR = 0xFF;//all output

	//port 1
	P1OUT &= BIT0;//not used, make output low
	P1OUT &= BIT3;//not used, make output low
	P1OUT &= BIT4;//not used, make output low
	P1OUT &= BIT5;//not used, make output low
	P1OUT &= BIT6;//not used, make output low
	P1OUT &= BIT7;//not used, make output low
	P1DIR |= BIT0;
	P1DIR |= BIT3;
	P1DIR |= BIT4;
	P1DIR |= BIT5;
	P1DIR |= BIT6;
	P1DIR |= BIT7;


	//P1DIR &= ~BIT1;//UART receive RXD
	P1SEL |= BIT1;//select UART function
	P1SEL2 |= BIT1;//select UART function

	//P1DIR |= BIT2;//UART transmit TXD
	P1SEL |= BIT2;//select UART function
	P1SEL2 |= BIT2;//select UART function


	//*****************************   DOES NOT WORK YET  *************************************
	//segment ID
	P2REN |= BIT0; //pullup resistors enabled
	P2REN |= BIT1;
	P2REN |= BIT2;

	P2OUT |= BIT0;//pull up
	P2OUT |= BIT1;//pull up
	P2OUT |= BIT2;//pull up

	//P2SEL &= ~BIT0; //
	//P2SEL &= ~BIT1;
	//P2SEL &= ~BIT2;

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
