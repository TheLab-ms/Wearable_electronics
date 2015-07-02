#include <msp430.h> 
#include <math.h>

#include "mydefines.h"

#define PI_DIV_BY_TWO 1.570796327


#define MAX(a,b)        (((a)>(b)) ? (a):(b))




// Prototypes ******************************
void init_clock(void);
void I2Cstart(void);
unsigned char writeI2C(unsigned char chip_address, unsigned int register_address, unsigned char num_addr_bytes, unsigned char data);//chip_address, register_address, num_addr_bytes
unsigned char I2Cwrite_chip_data(unsigned char data);
unsigned char readI2C(unsigned char chip_address, unsigned int register_address, unsigned char num_addr_bytes, unsigned char num_data_bytes);
unsigned char I2Cwrite_chip_address(unsigned char chip_address, unsigned char readwrite);//0=write  1=read
unsigned char I2CWrite_reg_addr(unsigned int register_address, unsigned char num_addr_bytes);
void i2c_data_low(void);
unsigned char getI2Cdata(void);
void I2Cstop(void);
void delay_100KHz(void);//10uS delay
void update_segment_ASCII(unsigned char seg_id, unsigned char ASCII_value);
void update_segment_font2(unsigned char seg_id, unsigned char font_value, unsigned char next_font_value, unsigned int offset);
void update_segment_LINE(unsigned char seg_id, char c1, char c2, char c3, char c4, char c5, char c6, char c7, char c8);

void Harris(int iNumData);
void myFFT(unsigned int iLength, unsigned char bAverage);
float sin2(unsigned int x);
float cos2(unsigned int x);


// Globals *****************************
unsigned char I2Creadbuf[35];
unsigned char gRed;
unsigned char gBlue;
unsigned char gGreen;
unsigned int A2Dcounts[128];
double A2Dvolts[128], m_dReal[128], m_dImaginary[128];
double m_dFFTOutData[128];


//delays...
//__delay_cycles(10000);//1.2mS
//__delay_cycles(35);//6.08
//__delay_cycles(70);//10.4
//__delay_cycles(86);//12.4
//__delay_cycles(90);//12.8
//__delay_cycles(200);//26
//__delay_cycles(1000);//120uS




//wI = sin(2*pi / M);//
//*************************************************************************************************
float sin2(unsigned int x)
{
	float result;

	switch (x)
	{
	case 2:
	result = .054803665;
	break;
	case 4:
	result = .027412134;
	break;
	case 8:
	result = .013707355;
	break;
	case 16:
	result = .006853838;
	break;
	case 32:
	result = .003426939;
	break;

	default:
		while(1);//trap
		break;

	}

   return result;
}


//wR = cos(2*pi / M);
//***********************************************************************************************
float cos2(unsigned int x)
{
	float result;

	switch (x)
	{
	case 2:
	result = .998497150;
	break;
	case 4:
	result = .999624217;
	break;
	case 8:
	result = .999906050;
	break;
	case 16:
	result = .999976512;
	break;
	case 32:
	result = .999994128;
	break;

	default:
		while(1);//trap
		break;

	}

   return result;

}







//  Central Processor
//  CP
//  CP
//  CP
//  CP


//********************************************************************************************************************
int main(void)
{
	unsigned char s, x, c1, c2, c3, c4, c5, c6, c7, c8, ccounter;
	volatile unsigned int vcounts, index;
	volatile int dB[10];

    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

    init_clock();


    i2c_data_takelow; //make data low when set to output
    i2c_data_in;      //iit data to input
    i2c_clk_high;     //init clock high
    i2c_clock_out;    //make the clock line an output

	select_global_colors(255,0,0);//red, blue, green



	P3DIR |= BIT6;

    P6SEL |= BIT0;                            // Enable A/D channel A6
	REFCTL0 |= REFMSTR+REFVSEL_1+REFON+REFTCOFF;// Enable 2.0V reference, disable temperature sensor to save power
	ADC12CTL0 = ADC12ON+ADC12SHT02;           // Turn on ADC12, set sampling time
	ADC12CTL1 = ADC12SHP;                     // Use sampling timer
	ADC12MCTL0 = ADC12SREF_1;                 // Vr+=Vref+ and Vr-=AVss - uses the internale reference selected above for the positive ref
	__delay_cycles(75);                       // 75 us delay @ ~1MHz
	ADC12CTL0 |= ADC12ENC;                    // Enable conversions




/*
	update_segment_LINE(1, 0,0,0,0,0,0,0,0);
	update_segment_LINE(1, 1,1,1,1,1,1,1,1);
	update_segment_LINE(1, 2,2,2,2,2,2,2,2);
	update_segment_LINE(1, 7,7,7,7,7,7,7,7);
	update_segment_LINE(1, 8,8,8,8,8,8,8,8);

	update_segment_LINE(2, 0,0,0,0,0,0,0,0);
	update_segment_LINE(3, 0,0,0,0,0,0,0,0);
	update_segment_LINE(4, 0,0,0,0,0,0,0,0);
	update_segment_LINE(5, 0,0,0,0,0,0,0,0);
	update_segment_LINE(6, 0,0,0,0,0,0,0,0);
	update_segment_LINE(7, 0,0,0,0,0,0,0,0);
	update_segment_LINE(8, 0,0,0,0,0,0,0,0);
while(1);
*/


	//*****************************************************************************************************************
	__delay_cycles(15000); //15000 (2mS) is the minimum delay between packets is writing to the same 8x8 array repeatedly
	//*****************************************************************************************************************

	//************************************************
	//*** Start Of Don's Spectral Output Test Code
	//************************************************
	/*
	ccounter=0;
	while(1)
	{

		ccounter++;
		if(ccounter>0)
		select_global_colors(255,0,0);//red, blue, green
		if(ccounter>30)
		select_global_colors(0,255,0);//red, blue, green
		if(ccounter>60)
		select_global_colors(0,0,255);//red, blue, green
		if(ccounter>90)
		select_global_colors(255,255,255);//red, blue, green
		if(ccounter>120)
			ccounter=0;

		index=0;
		for(index=0; index<16; index++) //acquire 16 samples
		{
			ADC12CTL0 |= ADC12SC;                   // Start conversion
			while (!(ADC12IFG & BIT0));
			A2Dcounts[index] = ADC12MEM0;
			P3OUT |= BIT6;//test pin to confirm exactly 20K sps
			//__delay_cycles(33);//39.4KHz
			__delay_cycles(235);//20.0KHz
			P3OUT &= ~BIT6;
		}

		for(index=0; index<16; index++)
		{
			A2Dvolts[index] = A2Dcounts[index] / 4095.0 * 2.0;
			A2Dvolts[index] -= 1.01;
		}

		//Harris(16);
		myFFT(16, 0);

		for(x=0; x<8; x++)
		{
			dB[x] = (int)((m_dFFTOutData[x] +30.0) / 4.0);  //scale and take integer value
			if(dB[x] <0) dB[x] = 0;
			if(dB[x] >8) dB[x] = 8;
		}

		update_segment_LINE(1, dB[0], dB[0], dB[0], dB[0], dB[0], dB[0], dB[0], dB[0]);//add a vertical line of desired height in the desired column - bottom justified
		__delay_cycles(15000);//1.2mS
		update_segment_LINE(2, dB[1], dB[1], dB[1], dB[1], dB[1], dB[1], dB[1], dB[1]);
		__delay_cycles(15000);//1.2mS
		update_segment_LINE(3, dB[2], dB[2], dB[2], dB[2], dB[2], dB[2], dB[2], dB[2]);
		__delay_cycles(15000);//1.2mS
		update_segment_LINE(4, dB[3], dB[3], dB[3], dB[3], dB[3], dB[3], dB[3], dB[3]);
		__delay_cycles(15000);//1.2mS
		update_segment_LINE(5, dB[4], dB[4], dB[4], dB[4], dB[4], dB[4], dB[4], dB[4]);
		__delay_cycles(15000);//1.2mS
		update_segment_LINE(6, dB[5], dB[5], dB[5], dB[5], dB[5], dB[5], dB[5], dB[5]);
		__delay_cycles(15000);//1.2mS
		update_segment_LINE(7, dB[6], dB[6], dB[6], dB[6], dB[6], dB[6], dB[6], dB[6]);
		__delay_cycles(15000);//1.2mS
		update_segment_LINE(8, dB[7], dB[7], dB[7], dB[7], dB[7], dB[7], dB[7], dB[7]);
		__delay_cycles(15000);//1.2mS
	}
	*/
	//************************************************
	//*** End Of Don's Spectral Output Test Code
	//************************************************


	//************************************************
	//*** Start Of Richard's Font Output Test Code
	//************************************************

	// ***
	// Below spells out T h e L A B . m s (space) in unicode HEX
	// ***
	const unsigned char charstodisplay[ ] = {0x54, 0x68, 0x65, 0x4C, 0x41, 0x42, 0x2E, 0x6D, 0x73, 0x00};

	// ***
	// Determine if you want scrolling text or not ** set scroll=1 to smooth scroll ** set scroll=2 to panel scroll
	// ***
	unsigned int scroll = 1;

	// ***
	// Set Starting Color
	// ***
	select_global_colors(255,0,0);
	ccounter=0;

	while(1)
	{
		// ***
		// Change Colors (stole this from Don's code above)
		// ***
		/*
		ccounter++;
		if(ccounter>0) { select_global_colors(255,0,0); }
		if(ccounter>30) { select_global_colors(0,255,0); }
		if(ccounter>60) { select_global_colors(0,0,255); }
		if(ccounter>90) { select_global_colors(255,255,255); }
		if(ccounter>120) { ccounter=0; }
		*/

		// ***
		// Display Our Text Sting In Chosen Scroll Format
		// ***
		if (scroll == 2)  //Panel Scroll
		{
			unsigned int csel1, csel2, csel3, csel4, csel5, csel6, csel7, csel8, sdly1;
			for (csel1=0; csel1<(sizeof(charstodisplay)); csel1++)
			{
				if( (csel1 + 1) > (sizeof(charstodisplay)-1) ) { csel2 = 0; } else { csel2 = csel1 + 1; }
				if( (csel2 + 1) > (sizeof(charstodisplay)-1) ) { csel3 = 0; } else { csel3 = csel2 + 1; }
				if( (csel3 + 1) > (sizeof(charstodisplay)-1) ) { csel4 = 0; } else { csel4 = csel3 + 1; }
				if( (csel4 + 1) > (sizeof(charstodisplay)-1) ) { csel5 = 0; } else { csel5 = csel4 + 1; }
				if( (csel5 + 1) > (sizeof(charstodisplay)-1) ) { csel6 = 0; } else { csel6 = csel5 + 1; }
				if( (csel6 + 1) > (sizeof(charstodisplay)-1) ) { csel7 = 0; } else { csel7 = csel6 + 1; }
				if( (csel7 + 1) > (sizeof(charstodisplay)-1) ) { csel8 = 0; } else { csel8 = csel7 + 1; }
				for (sdly1=0; sdly1<50; sdly1++)
				{
					update_segment_font2(1, charstodisplay[csel1], 0, 0 );
					__delay_cycles(13000);//delay needed between writes to the G2s so they can keep up...
					update_segment_font2(2, charstodisplay[csel2], 0, 0 );
					__delay_cycles(13000);//delay needed between writes to the G2s so they can keep up...
					update_segment_font2(3, charstodisplay[csel3], 0, 0 );
					__delay_cycles(13000);//delay needed between writes to the G2s so they can keep up...
					update_segment_font2(4, charstodisplay[csel4], 0, 0 );
					__delay_cycles(13000);//delay needed between writes to the G2s so they can keep up...
					update_segment_font2(5, charstodisplay[csel5], 0, 0 );
					__delay_cycles(13000);//delay needed between writes to the G2s so they can keep up...
					update_segment_font2(6, charstodisplay[csel6], 0, 0 );
					__delay_cycles(13000);//delay needed between writes to the G2s so they can keep up...
					update_segment_font2(7, charstodisplay[csel7], 0, 0 );
					__delay_cycles(13000);//delay needed between writes to the G2s so they can keep up...
					update_segment_font2(8, charstodisplay[csel8], 0, 0 );
					__delay_cycles(13000);//delay needed between writes to the G2s so they can keep up...
				}
				// ***
				// Change Colors (stole this from Don's code above)
				// ***
				ccounter++;
				if(ccounter>0) { select_global_colors(255,0,0); }
				if(ccounter>8) { select_global_colors(0,255,0); }
				if(ccounter>16) { select_global_colors(0,0,255); }
				if(ccounter>24) { select_global_colors(255,255,255); }
				if(ccounter>32) { ccounter=0; }
			}

		} else if (scroll == 1) // Smooth Scroll
		{
			unsigned int csel1, csel2, csel3, csel4, csel5, csel6, csel7, csel8, csel9, sdly1, offset;
			for (csel1=0; csel1<(sizeof(charstodisplay)); csel1++)
			{
				if( (csel1 + 1) > (sizeof(charstodisplay)-1) ) { csel2 = 0; } else { csel2 = csel1 + 1; }
				if( (csel2 + 1) > (sizeof(charstodisplay)-1) ) { csel3 = 0; } else { csel3 = csel2 + 1; }
				if( (csel3 + 1) > (sizeof(charstodisplay)-1) ) { csel4 = 0; } else { csel4 = csel3 + 1; }
				if( (csel4 + 1) > (sizeof(charstodisplay)-1) ) { csel5 = 0; } else { csel5 = csel4 + 1; }
				if( (csel5 + 1) > (sizeof(charstodisplay)-1) ) { csel6 = 0; } else { csel6 = csel5 + 1; }
				if( (csel6 + 1) > (sizeof(charstodisplay)-1) ) { csel7 = 0; } else { csel7 = csel6 + 1; }
				if( (csel7 + 1) > (sizeof(charstodisplay)-1) ) { csel8 = 0; } else { csel8 = csel7 + 1; }
				if( (csel8 + 1) > (sizeof(charstodisplay)-1) ) { csel9 = 0; } else { csel9 = csel8 + 1; }
				for (offset=0; offset<9; offset++)
				{

					for (sdly1=0; sdly1<10; sdly1++)
					{
						update_segment_font2(1, charstodisplay[csel1], charstodisplay[csel2], offset );
						__delay_cycles(13000);//delay needed between writes to the G2s so they can keep up...
						update_segment_font2(2, charstodisplay[csel2], charstodisplay[csel3], offset );
						__delay_cycles(13000);//delay needed between writes to the G2s so they can keep up...
						update_segment_font2(3, charstodisplay[csel3], charstodisplay[csel4], offset );
						__delay_cycles(13000);//delay needed between writes to the G2s so they can keep up...
						update_segment_font2(4, charstodisplay[csel4], charstodisplay[csel5], offset );
						__delay_cycles(13000);//delay needed between writes to the G2s so they can keep up...
						update_segment_font2(5, charstodisplay[csel5], charstodisplay[csel6], offset );
						__delay_cycles(13000);//delay needed between writes to the G2s so they can keep up...
						update_segment_font2(6, charstodisplay[csel6], charstodisplay[csel7], offset );
						__delay_cycles(13000);//delay needed between writes to the G2s so they can keep up...
						update_segment_font2(7, charstodisplay[csel7], charstodisplay[csel8], offset );
						__delay_cycles(13000);//delay needed between writes to the G2s so they can keep up...
						update_segment_font2(8, charstodisplay[csel8], charstodisplay[csel9], offset );
						__delay_cycles(13000);//delay needed between writes to the G2s so they can keep up...
					}
					// ***
					// Change Colors (stole this from Don's code above)
					// ***
					ccounter++;
					if(ccounter>0) { select_global_colors(255,0,0); }
					if(ccounter>8) { select_global_colors(0,255,0); }
					if(ccounter>16) { select_global_colors(0,0,255); }
					if(ccounter>24) { select_global_colors(255,255,255); }
					if(ccounter>32) { ccounter=0; }

				}

			}

		} else // Static Display - No Scroll - Only First 8 Array Elements Used
		{
			update_segment_font2(1, charstodisplay[0], 0, 0 );
			__delay_cycles(13000);//delay needed between writes to the G2s so they can keep up...
			update_segment_font2(2, charstodisplay[1], 0, 0 );
			__delay_cycles(13000);//delay needed between writes to the G2s so they can keep up...
			update_segment_font2(3, charstodisplay[2], 0, 0 );
			__delay_cycles(13000);//delay needed between writes to the G2s so they can keep up...
			update_segment_font2(4, charstodisplay[3], 0, 0 );
			__delay_cycles(13000);//delay needed between writes to the G2s so they can keep up...
			update_segment_font2(5, charstodisplay[4], 0, 0 );
			__delay_cycles(13000);//delay needed between writes to the G2s so they can keep up...
			update_segment_font2(6, charstodisplay[5], 0, 0 );
			__delay_cycles(13000);//delay needed between writes to the G2s so they can keep up...
			update_segment_font2(7, charstodisplay[6], 0, 0 );
			__delay_cycles(13000);//delay needed between writes to the G2s so they can keep up...
			update_segment_font2(8, charstodisplay[7], 0, 0 );
			__delay_cycles(13000);//delay needed between writes to the G2s so they can keep up...
			// ***
			// Change Colors (stole this from Don's code above)
			// ***
			ccounter++;
			if(ccounter>0) { select_global_colors(255,0,0); }
			if(ccounter>30) { select_global_colors(0,255,0); }
			if(ccounter>60) { select_global_colors(0,0,255); }
			if(ccounter>90) { select_global_colors(255,255,255); }
			if(ccounter>120) { ccounter=0; }
		}

	}

	//************************************************
	//*** End Of Richard's Font Output Test Code
	//************************************************



/*	while(1)
	{
		index=0;
		for(index=0; index<128; index++) //acquire 128 samples
		{
			ADC12CTL0 |= ADC12SC;                   // Start conversion
			while (!(ADC12IFG & BIT0));
			A2Dcounts[index] = ADC12MEM0;
			__delay_cycles(33);
			P3OUT |= BIT6;//test pin to confirm exactly 40K sps
			P3OUT &= ~BIT6;
		}

		for(index=0; index<128; index++)
		{
			A2Dvolts[index] = A2Dcounts[index] / 4095.0 * 2.0;
			A2Dvolts[index] -= 1.0;
		}

			Harris(128);
			myFFT(128, 0);
	}
*/
	while(1);



	//P3OUT ^= BIT6;//test pin to confirm exactly 40K sps

	//update_segment_LINE(8, 1, 1, 1, 1, 1, 1, 1, 1);//add a vertical line of desired height in the desired column - bottom justified
	//__delay_cycles(50000);//1.2mS



//    	update_segment_ASCII(1, 33);
//        __delay_cycles(13000);//delay needed between writes to the G2s so they can keep up...


/*
    P3DIR |= BIT0;//out
    while(1)
    {
       	P3OUT |= BIT0;//high
      	P3OUT &= ~BIT0;//low
       	P3OUT |= BIT0;//high
       	P3OUT &= ~BIT0;//low
    	delay_100KHz();//5uS delay
       	P3OUT |= BIT0;//high
      	P3OUT &= ~BIT0;//low
       	P3OUT |= BIT0;//high
       	P3OUT &= ~BIT0;//low
    }*/


	return 0;
}


//******************************************************************************************************************
void update_segment_ASCII(unsigned char seg_id, unsigned char ASCII_value)
{
    I2Cstart();
    I2Cwrite_chip_address(seg_id, 0);//0=write  1=read //address i2c destination in G2 silicon
    I2Cwrite_chip_data(seg_id);//address the i2c destination G2 in firmware
    I2Cwrite_chip_data(11);//ASCII (not binary)
    I2Cwrite_chip_data(gRed);
    I2Cwrite_chip_data(gBlue);
    I2Cwrite_chip_data(gGreen);
    I2Cwrite_chip_data(ASCII_value);//desired ASCII character - decimal ASCII code EX: ASCII "!" = decimal 33
    I2Cwrite_chip_data(9);//packet terminator
    I2Cstop();
}

//******************************************************************************************************************
void update_segment_font2(unsigned char seg_id, unsigned char font_value, unsigned char next_font_value, unsigned int offset)
{
	font_value+=10;
	next_font_value+=10;
	offset+=10;
    I2Cstart();
    I2Cwrite_chip_address(seg_id, 0);//0=write  1=read //address i2c destination in G2 silicon
    I2Cwrite_chip_data(seg_id);//address the i2c destination G2 in firmware
    I2Cwrite_chip_data(12);
    I2Cwrite_chip_data(gRed);
    I2Cwrite_chip_data(gBlue);
    I2Cwrite_chip_data(gGreen);
    I2Cwrite_chip_data(font_value);//desired font character - HEX unicode value EX: "J" = 4A
    I2Cwrite_chip_data(next_font_value);//next desired font character - HEX unicode value EX: "J" = 4A
    I2Cwrite_chip_data(offset);
    I2Cwrite_chip_data(9);//packet terminator
    I2Cstop();
}

//******************************************************************************************************************
void update_segment_LINE(unsigned char seg_id, char c1, char c2, char c3, char c4, char c5, char c6, char c7, char c8)//must be values from 0 to 8
{
	//sence we cannot send values 1-8 in the packet lets increment by 10 first
	//these numbers indicate how many of the 8 LEDs in the column to turn on
	c1+=10;
	c2+=10;
	c3+=10;
	c4+=10;
	c5+=10;
	c6+=10;
	c7+=10;
	c8+=10;

	if(gRed<10) gRed=10;
	if(gBlue<10) gBlue=10;
	if(gGreen<10) gGreen=10;


    I2Cstart();
    I2Cwrite_chip_address(seg_id, 0);//0=write  1=read //address i2c destination in G2 silicon
    I2Cwrite_chip_data(seg_id);//address the i2c destination G2 in firmware
    I2Cwrite_chip_data(22);//Vertical line - bottom justified

    I2Cwrite_chip_data(gRed);
    I2Cwrite_chip_data(gBlue);
    I2Cwrite_chip_data(gGreen);
    I2Cwrite_chip_data(c1);//height of column 1
    I2Cwrite_chip_data(c2);//height of column 2
    I2Cwrite_chip_data(c3);//height of column 3
    I2Cwrite_chip_data(c4);//height of column 4
    I2Cwrite_chip_data(c5);//height of column 5
    I2Cwrite_chip_data(c6);//height of column 6
    I2Cwrite_chip_data(c7);//height of column 7
    I2Cwrite_chip_data(c8);//height of column 8
    I2Cwrite_chip_data(9);//packet terminator
    I2Cstop();
}



//******************************************************************************************************************
void delay_100KHz()//100KHz = 10uS.  bit time delay is 5uS
{
	__delay_cycles(15);//86KHz I2C clock

	//__delay_cycles(1);//155KHz I2C clock

}


//***********************************************************************************************
void select_global_colors(unsigned char r, unsigned char b, unsigned char g)
{
	if(r<10) r=10;
	if(b<10) b=10;
	if(g<10) g=10;

    gRed = r;
    gBlue = b;
    gGreen = g;

}



//***********************************************************************************************
void init_clock()
{
	P11DIR |= 0x07;                           // ACLK, MCLK, SMCLK set out to pins
	P11SEL |= 0x07;                           // P11.0,1,2 for debugging purposes.

	UCSCTL3 |= SELREF_2;                      // Set DCO FLL reference = REFO
	UCSCTL4 |= SELA_2;                        // Set ACLK = REFO

	__bis_SR_register(SCG0);                  // Disable the FLL control loop
	UCSCTL0 = 0x0000;                         // Set lowest possible DCOx, MODx
	UCSCTL1 = DCORSEL_5;                      // Select DCO range 16MHz operation
	UCSCTL2 = FLLD_1 + 249;                   // Set DCO Multiplier for 8MHz
											  // (N + 1) * FLLRef = Fdco
											  // (249 + 1) * 32768 = 8MHz
											  // Set FLL Div = fDCOCLK/2
	__bic_SR_register(SCG0);                  // Enable the FLL control loop

	// Worst-case settling time for the DCO when the DCO range bits have been
	// changed is n x 32 x 32 x f_MCLK / f_FLL_reference. See UCS chapter in 5xx
	// UG for optimization.
	// 32 x 32 x 8 MHz / 32,768 Hz = 250000 = MCLK cycles for DCO to settle
	__delay_cycles(250000);

	// Loop until XT1,XT2 & DCO fault flag is cleared
	do
	{
	  UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + XT1HFOFFG + DCOFFG);
											  // Clear XT2,XT1,DCO fault flags
	  SFRIFG1 &= ~OFIFG;                      // Clear fault flags
	}while (SFRIFG1&OFIFG);                   // Test oscillator fault flag

}


//******************************************************************************************************************
void I2Cstart(void)
{
	//data goes low while clock is high
	i2c_clk_high;//just in case its low...
	delay_100KHz();
	i2c_data_low();
	delay_100KHz();
	i2c_clk_low; //make ready to clock data
	delay_100KHz();
}



//******************************************************************************************************************
unsigned char I2Cwrite_chip_data(unsigned char data)
{
	volatile unsigned char bitpos;//, databyte;

	bitpos=0x80;
	while(bitpos)
	{
		//8-bit data
		if(data & bitpos)//if current position is high
			i2c_data_in;
		  else
			i2c_data_low();

		delay_100KHz();
		i2c_clk_high;
		bitpos >>= 1;
		delay_100KHz();
		i2c_clk_low;
	}

	//read the ACK/NACK
	i2c_data_in;//make data an input to read the ACK
	delay_100KHz();
	i2c_clk_high;
	delay_100KHz();
	//read data state
	bitpos = getI2Cdata();
	delay_100KHz();
	i2c_clk_low;
	delay_100KHz();

	if(bitpos==1)//error
		return 1;

	return 0;
}





//******************************************************************************************************************
unsigned char I2Cwrite_chip_address(unsigned char chip_address, unsigned char readwrite)//0=write  1=read
{
	volatile unsigned char bitpos, temp;

	temp=chip_address;//this added because code composer

	temp--;      //segments 1-8 maps to 0-7 for the actual address via IO pins for each G2 micro
	temp <<= 1;  //shift left so can set/clear for read/write command

	temp &= 0xFE; //start with address set to write mode
	if(readwrite)
		temp |= 0x01; //set to read mode

	bitpos=0x80;
	while(bitpos)
	{
		//8-bit data
		if(temp & bitpos)//if current position is high
			i2c_data_in;
		  else
			i2c_data_low();

		delay_100KHz();
		i2c_clk_high;
		bitpos >>= 1;
		delay_100KHz();
		i2c_clk_low;
	}

	//read the ACK/NACK
	i2c_data_in;//make data an input to read the ACK
	delay_100KHz();
	delay_100KHz();

	i2c_clk_high;
	delay_100KHz();
	//read data state
	bitpos = getI2Cdata();
	delay_100KHz();
	i2c_clk_low;
	delay_100KHz();

	if(bitpos==1)//error
		return 1;

	return 0;
}




//*****************************************************************************************************************
void i2c_data_low()
{
	i2c_datadir_out;

}



//******************************************************************************************************************
 unsigned char getI2Cdata()
 {
	 volatile unsigned char ret;

	 ret = P10IN;	//read port P1.6

	 ret &= BIT7;	//mask off other port bits
	 ret >>= 7;		//move bit received to LSB

	 return ret;
 }

//******************************************************************************************************************
void I2Cstop(void)
{
	//data goes high while clock is high
	i2c_data_low();//just in case it was low...
	delay_100KHz();
	i2c_clk_high;
	delay_100KHz();
	i2c_data_in;
	delay_100KHz();
}



//Computes the Blackman-Harris window and applies it to the input data before
//frequency analysis is performed.
//The Blakcman-Harris window is defined by the equation:
//w(n) = a0 - a1cos(2pi*n/N-1) + a2cos(4pi*n/N-1) - a3cos(6pi*n/N-1)
//a0 = 0.35875
//a1 = 0.48829
//a2 = 0.14128
//a3 = 0.01168
//void CQFUtilsManager::FPGAData_Harris(unsigned char ucControllerId, int iChannel, int iNumData) orig
//**************************************************************************************************************************************
void Harris(int iNumData)
{
	//int iMaxChan = MAX_DISPLAY_OUTPUT_CHANNELS;
	//if (iNumData <= 0 || iNumData >= RXSIZE) return;
	//if (iChannel < 0 || iChannel >= iMaxChan) return;
	//if (ucControllerId >= MAX_CHIP_CONTROLLERS) return;
	double harris, factor, arg;
	unsigned int i;

	factor = 8.0 * atan(1.0) / (double)iNumData;

//*****  1  ****************************************************************************************
P3OUT |= BIT6;//test pin to confirm exactly 40K sps
P3OUT &= ~BIT6;

	for (i=0; i<iNumData; i++)
	{
		arg = factor * (double) i;
		harris = 0.35875 - 0.48829*cos(arg) + 0.14128*cos(2*arg) - 0.01168*cos(3*arg);

		A2Dvolts[i] = A2Dvolts[i] * harris;
		//m_dVolt[ucControllerId][iChannel][i] = m_dVolt[ucControllerId][iChannel][i] * harris;
	 }

//*****  2  ****************************************************************************************
P3OUT |= BIT6;//test pin to confirm exactly 40K sps
P3OUT &= ~BIT6;
P3OUT |= BIT6;//test pin to confirm exactly 40K sps
P3OUT &= ~BIT6;

}





//  Computes the power spectrum of the input data using a Decimate in Time DDT computation.
//  The data has been windowed using a Blackman-Harris window in
//  Harris().  In this function the following steps are performed:
//  1.  The input data is reordered as per the DIT FFT algorithm.
//  2.  The butterfly stages of the FFT are done.
//  3.  The magnitude squared of each bin is calculated.
//  4.  An amplitude correction is applied
//  5.  The bins are optionally averaged with previous bin values (assumes a
//      running FFT calculation).
//  6.  The bins or averaged bins are divided by a factor
//void CQFUtilsManager::FPGAData_ChannelFFT(unsigned char ucControllerId, int iChannel, int iLength, bool bAverage)
//**************************************************************************************************************************************
void myFFT(unsigned int iLength, unsigned char bAverage)
{
	//int iMaxChan = MAX_DISPLAY_OUTPUT_CHANNELS;
	//if (iLength <= 0 || iLength >= RXSIZE) return;
	//if (iChannel < 0 || iChannel >= iMaxChan) return;
	//if (ucControllerId >= MAX_CHIP_CONTROLLERS) return;

	// Local variables used in FFT calc
	//	int m;
	//	int L, l1, l2, k1;
	volatile unsigned int iHalfInputData, i, k, j;
	//	double ix, a, r, u, v, w, u0;
	//	double pi;
	//	int iBasedIndex = 1;
	volatile double maxMag;
	volatile double real;
	volatile double img;
	volatile double val;

	// Local variables used in FFT calc
	volatile unsigned int    p, q, L,                                   // Counters and indices
         M;                                          // Stages of FFT
	volatile double aR, aI, bR, bI, vR, vI, wR, wI, TmpR, TmpI; // Complex varibles


	volatile double pi;
	//pi = 4.0 * atan(1.0);
	pi = 3.141592654;


	// Initialize FFT variables
	for (i=0; i<iLength; i++)
	{
		m_dReal[i] = 0.0;
		m_dImaginary[i] = 0.0;
	}

	//ktimes = 1;  // input array / output array - usually 1
	iHalfInputData = (iLength/2);   // half of the input data

	//  Seed the FFT input with the A/D input.  The imag part is 0 since the input
	//  data is real.
	for (k=0; k<iLength; k++)
	{
		m_dReal[k] = A2Dvolts[k];
		m_dImaginary[k] = 0.0;
	}


	///////////////////////////////////////////////////////////////////////////
	// This section reorders the inputs as required by the Decimation in Time
	// FFT algorithm.  The inputs are reordered so that when the FFT calculation
	// is done, the outputs are already in the right order.
	///////////////////////////////////////////////////////////////////////////
	j = 0;
	k = 0;
	for (k=0; k<iLength; k++)
	{
		// Swap the inputs
		if (k<j)
		{
			TmpR = m_dReal[k];
			TmpI = m_dImaginary[k];
			m_dReal[k] = m_dReal[j];
			m_dImaginary[k] = m_dImaginary[j];
			m_dReal[j] = TmpR;
			m_dImaginary[j] = TmpI;
		}

		// Update the index
		L = iLength / 2;
		while ( L <= j && L > 0 )
		{
			j = j - L;
			L = (int)(L / 2);
		}

		j = j + L;
	}



	///////////////////////////////////////////////////////////////////////////
	// This section performs the FFT.  The butterfly sections are done starting
	// with the 2 point butterfly.  There are m buterfly stages.
	//
	///////////////////////////////////////////////////////////////////////////
	M = 2;
	while (M <= iLength)   // Loop through butterfly stages
	{
		// Amount to rotate twiddle factors on each stage
		wR = cos(2*pi / M);
		wI = sin(2*pi / M);//-12800 w/o math.h,  -4.102e-10 !!! for sin(pi);
		//these take 11mS longer - keep for larger FFTs

		//wR = cos2(M);
		//wI = sin2(M);//M=2,4,8,16,32,etc
		//35mS

		// Initial twiddle factor
		vR = 1;
		vI = 0;
		for (k=0; k<M/2; k++)
		{
			for(i=0; i<iLength; i += M)
			{
				p = k + i;
				q = p + M/2;
				aR = m_dReal[p]; aI = m_dImaginary[p];
				// Complex Mult
				bR = m_dReal[q]*vR - m_dImaginary[q]*vI;
				bI = m_dImaginary[q]*vR + m_dReal[q]*vI;
				// Complex Add
				m_dReal[p] = aR + bR;
				m_dImaginary[p] = aI + bI;
				// Complex Sub
				m_dReal[q] = aR - bR;
				m_dImaginary[q] = aI - bI;
			}
			// Rotate the twiddle factor
			TmpR = vR*wR - vI*wI;
			vI   = vI*wR + vR*wI;
			vR   = TmpR;
		}
		// Advance to next stage
		M = 2*M;
	}



	///////////////////////////////////////////////////////////////////////////
	// This section computes the normalized Power Spectrum.
	// The Power Spectrum is calculated as follows:
	//
	// PS = 10*log10((xReal^2 + xImag^2)/(max(xReal^2 + xImag^2)))
	//
	// Optionally, this value is averaged with the previous values for that
	// given bin.
	///////////////////////////////////////////////////////////////////////////

	// After the FFT, we have 1/2 the input data.  So, all operations
	// are done with iHalfInputData.

	maxMag = 0;  // Max bin magnitude



	for (j=0; j<iHalfInputData; j++)
	{

		real = m_dReal[j];
		img = m_dImaginary[j];

		// Compute the magnitude squared
		val = (real * real) + (img*img);
		m_dFFTOutData[j] = val;

		//if (bAverage)		{
		//	 m_dFFTOutDataAvg[ucControllerId][iChannel][j] += m_dFFTOutData[ucControllerId][iChannel][j];
		//	m_dFFTOutData[ucControllerId][iChannel][j] = m_dFFTOutDataAvg[ucControllerId][iChannel][j] / (double) m_uiPerAvNumber[ucControllerId];
		//}

		// Search for the largest mag squared or average mag squared
		if (m_dFFTOutData[j] > maxMag)
		{
			maxMag = m_dFFTOutData[j];
		}
	}

	// Normalize Power Spectrum and put in dB form
	// Using 10*log10 instead of 20*log10 to eliminate sqrt calc
	for(j=0; j<iHalfInputData; j++)
	{
		// For now remove the normalization
		//m_dFFTOutData[j] = 10 * log10( max(1.e-14, (m_dFFTOutData[j]/maxMag)));

		m_dFFTOutData[j] = 10 * log10( MAX(1.e-14, m_dFFTOutData[j]));
	}

	return;
}


















