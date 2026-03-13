#include<lpc21xx.h>
typedef unsigned int U32;

void delay_second(U32 second);
void delay_millisecond(U32 ms);
void delay_microsecond(U32 mics);


void delay_second(U32 second)
{
	T0PR=15000000-1;
	T0TCR=0X01;
	while(T0TC<second);
	T0TCR=0X03;
	T0TCR=0X00;
}
void delay_millisecond(U32 ms)
{
	T0PR=15000-1;
	T0TCR=0X01;
	while(T0TC<ms);
	T0TCR=0X03;
	T0TCR=0X00;
}
void delay_microsecond(U32 mics)
{
	T0PR=15-1;
	T0TCR=0X01;
	while(T0TC<mics);
	T0TCR=0X03;
	T0TCR=0X00;
}


	
