#include<lpc21xx.h>
#include<stdio.h>
#include<string.h>
#include"delay.h"
#include"fundefine.h"
char ch[20];
void ESP_send_data(unsigned int temp, unsigned int IRV)
{
    char send_buffer[200];
    char get_data[200];
	
		//close previous connection
		UART0_string_TX("AT+CIPCLOSE\r\n");
    delay_second(2);
	
		//start TCP
		sprintf(send_buffer,"AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n");
		UART0_string_TX(send_buffer); 
		delay_second(2);

    // Create GET request
   sprintf(get_data,"GET /update?api_key=OVTVQ8ESX533K6FM&field1=%u &field2=%u HTTP/1.1\r\nHost: api.thingspeak.com\r\n\r\n",temp, IRV);

    sprintf(send_buffer,"AT+CIPSEND=%d\r\n",strlen(get_data));
    UART0_string_TX(send_buffer);
    delay_second(2);

    UART0_string_TX(get_data);
    delay_second(2);
}
int ESP_send_command(char *cmd, char *expected)
{
    char response[200];   // Buffer to store ESP reply
    int i = 0;            // Index for buffer
    int timeout = 3000;   // Wait time (approx 3 seconds)
   
		UART0_string_TX(cmd);   //Send command to ESP

    
    while(timeout > 0)      //Wait and read response
    {
        if(U0LSR & 0x01)    // Check if data received from ESP
        {
            response[i] = U0RBR;  // Read received byte
            i++;      
            
					if(i >= 199)           // Prevent buffer overflow
                break;
        }
        delay_millisecond(1);   // Wait 1 ms
				timeout--;              // Reduce timeout
    }

    response[i] = '\0';          //End the string properly

   
    if(strstr(response, expected) != NULL)  //Check if expected word (like "OK") is inside response
    {
        return 1;   // Success
    }
    else
    {
        return 0;   // Failed
    }
}

