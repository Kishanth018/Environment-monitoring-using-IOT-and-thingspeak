#include<lpc21xx.h>
#include<stdio.h>
#include"fundefine.h"
#include"ESP_DATA.h"
#define IR 15

unsigned int IRV,temperature;
float LM35_volt;            
//char buffer[100];                                    //store the temperature and ldr data in buffer

int main()
{
	UART0_INIT();                 //UART initialization
	SPI0_INIT();								 //spi initialization
	IOSET0|=1<<7;                 //0.7 for chip select(cs)

	//=============ESP INIT===============
	if(ESP_send_command("AT\r\n", "OK")==0)
	{
		UART0_string_TX("ESP Connection failed to response\n");
    while(1);  
	}

	UART0_string_TX("AT+CWMODE=1\r\n");
	delay_second(2);

	UART0_string_TX("AT+CWJAP=\"Realme\",\"kishanth2004\"\r\n");
	delay_second(5);
	
	UART0_string_TX("AT+CIFSR\r\n");
	delay_second(2);


	while(1)
	{
	    
		LM35_volt=read_mcp3204(0);    					//read LM35 from channel 0
		temperature=LM35_volt/0.1;    				 //10mV per celsius
		
	  	IRV=((IOPIN0>>IR)&1); //IR value
		
		ESP_send_data(temperature,IRV);
		delay_second(16);
		
		//sprintf(buffer,"Temp=%u C|LDR=%u V \r\n",temperature,IRV); 
		
	//	UART0_string_TX(buffer);             //Transmit buffer in UART0 
	//	delay_second(2);                    //delay for 2sec for next reading
	}
}
void SPI0_INIT(void)
{
	PINSEL0|=0x1500;                      //p0.4 as SCK p0.5 as MISO p0.6 as MOSI
	IODIR0|=1<<7;                       	//output pin for CS 0.7
	S0SPCCR=150;											 //clock speed =pclk/spi rate  pclk=15000000 spi rate=100kbps clock speed=150
	S0SPCR|=(1<<5)|(0x18);        			//selecting master and mode as 3 by writing 1 in CPOL,CPHA
}
unsigned char SPI0_DATA(unsigned char data)
{
	unsigned char temp = S0SPCR;                //dummy
	S0SPDR=data;                              
	while(((S0SPSR>>7)&1)==0);                 //wait for bit transfer flag become 1
	return S0SPDR;                            //sent bits to buffer
}
float read_mcp3204(unsigned int channel)
{
	unsigned char Hbyte,Lbyte;
	unsigned int adc_val;
	IOCLR0|=1<<7;                            		  //make CS low for bit shifting
	SPI0_DATA(0x06); 	                					 //start condition and select single or differential input
	Hbyte=SPI0_DATA(channel<<6);      					//send channel number in 6th bit for channel selection
	Lbyte=SPI0_DATA(0x00);
	IOSET0|=1<<7;         				              	//after bit shifting make cs high
	adc_val=(Hbyte&0x0F)<<8|Lbyte;	    	 //total 12bits Hbyte 4bits and Lbyte 8bits
	return (adc_val*3.3)/4096;           		  //obtained value*3.3(Vref-reference voltage)/4096 2^12 (12bits)
}

//==============UART0====================

void UART0_INIT()
{
	PINSEL0|=0x05;
	U0LCR=0x83;
	U0DLL=97;
	U0DLM=0;
	U0LCR=0x03;
}
unsigned char UART0_RX(void)
{
	while(((U0LSR>>0)&1)==0);
	return U0RBR;
}
void UART0_string_TX(char*str)
{
	while(*str)
	{
		U0THR=*str++;
		while(((U0LSR>>5)&1)==0);
	}
}
