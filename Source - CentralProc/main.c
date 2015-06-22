#include <msp430.h> 
#include "mydefines.h"


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
void update_segment_LINE(unsigned char seg_id, char c1, char c2, char c3, char c4, char c5, char c6, char c7, char c8);



// Globals *****************************
unsigned char I2Creadbuf[35];
unsigned char gRed;
unsigned char gBlue;
unsigned char gGreen;

//delays...
//__delay_cycles(10000);//1.2mS
//__delay_cycles(35);//6.08
//__delay_cycles(70);//10.4
//__delay_cycles(86);//12.4
//__delay_cycles(90);//12.8
//__delay_cycles(200);//26
//__delay_cycles(1000);//120uS


//  CP
//  CP
//  CP
//  CP
//  CP


//********************************************************************************************************************
int main(void)
{
	unsigned char s, x, c1, c2, c3, c4, c5, c6, c7, c8;

    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

    init_clock();


    i2c_data_takelow; //make data low when set to output
    i2c_data_in;      //iit data to input
    i2c_clk_high;     //init clock high
    i2c_clock_out;    //make the clock line an output

    select_global_colors(255,255,255);//red, blue, green

/*
	update_segment_LINE(1, 1, 2, 3, 4, 5, 6, 7, 8);//add a vertical line of desired height in the desired column - bottom justified
	__delay_cycles(50000);//1.2mS
	update_segment_LINE(2, 1, 2, 3, 4, 5, 6, 7, 8);//add a vertical line of desired height in the desired column - bottom justified
	__delay_cycles(50000);//1.2mS
	update_segment_LINE(3, 1, 2, 3, 4, 5, 6, 7, 8);//add a vertical line of desired height in the desired column - bottom justified
	__delay_cycles(50000);//1.2mS
	update_segment_LINE(4, 1, 2, 3, 4, 5, 6, 7, 8);//add a vertical line of desired height in the desired column - bottom justified
	__delay_cycles(50000);//1.2mS
	update_segment_LINE(5, 1, 2, 3, 4, 5, 6, 7, 8);//add a vertical line of desired height in the desired column - bottom justified
	__delay_cycles(50000);//1.2mS
	update_segment_LINE(6, 1, 2, 3, 4, 5, 6, 7, 8);//add a vertical line of desired height in the desired column - bottom justified
	__delay_cycles(50000);//1.2mS
	update_segment_LINE(7, 1, 2, 3, 4, 5, 6, 7, 8);//add a vertical line of desired height in the desired column - bottom justified
	__delay_cycles(50000);//1.2mS
	update_segment_LINE(8, 1, 2, 3, 4, 5, 6, 7, 8);//add a vertical line of desired height in the desired column - bottom justified
	__delay_cycles(50000);//1.2mS
*/


    s=0;

    while(1)
    {
		for(x=1; x<9; x++)
		{
			c1=s++;
			if(s>8) s=1;
			c2=s++;
			if(s>8) s=1;
			c3=s++;
			if(s>8) s=1;
			c4=s++;
			if(s>8) s=1;
			c5=s++;
			if(s>8) s=1;
			c6=s++;
			if(s>8) s=1;
			c7=s++;
			if(s>8) s=1;
			c8=s++;
			if(s>8) s=1;

			update_segment_LINE(x, c1, c2, c3, c4, c5, c6, c7, c8);//add a vertical line of desired height in the desired column - bottom justified

			__delay_cycles(500000);//1.2mS
		}

		s+=3;
    }




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
	//__delay_cycles(15);//86KHz I2C clock

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

		//delay_100KHz();
		i2c_clk_high;
		bitpos >>= 1;
		//delay_100KHz();
		i2c_clk_low;
	}

	//read the ACK/NACK
	i2c_data_in;//make data an input to read the ACK
	//delay_100KHz();
	i2c_clk_high;
	//delay_100KHz();
	//read data state
	bitpos = getI2Cdata();
	//delay_100KHz();
	i2c_clk_low;
	//delay_100KHz();

	if(bitpos==1)//error
		return 1;

	return 0;
}





//******************************************************************************************************************
unsigned char I2Cwrite_chip_address(unsigned char chip_address, unsigned char readwrite)//0=write  1=read
{
	volatile unsigned char bitpos;

	chip_address &= 0xFE; //start with address set to write mode
	if(readwrite)
		chip_address |= 0x01; //set to read mode

	bitpos=0x80;
	while(bitpos)
	{
		//8-bit data
		if(chip_address & bitpos)//if current position is high
			i2c_data_in;
		  else
			i2c_data_low();

		//delay_100KHz();
		i2c_clk_high;
		bitpos >>= 1;
		//delay_100KHz();
		i2c_clk_low;
	}

	//read the ACK/NACK
	i2c_data_in;//make data an input to read the ACK
	//delay_100KHz();
	//delay_100KHz();

	i2c_clk_high;
	//delay_100KHz();
	//read data state
	bitpos = getI2Cdata();
	//delay_100KHz();
	i2c_clk_low;
	//delay_100KHz();

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




















