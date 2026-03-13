#include<lpc21xx.h>
#include<stdio.h>

void SPI0_INIT(void);
unsigned char SPI0_DATA(unsigned char);
float read_mcp3204(unsigned int);
void UART0_INIT(void);
unsigned char UART0_RX(void);
void UART0_string_TX(char*str);
