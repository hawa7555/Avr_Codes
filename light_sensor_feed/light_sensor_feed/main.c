#define F_CPU 16000000UL

#include<avr/io.h>
#include<util/delay.h>
#include"uart.h"
#include"adc.h"

void uart_init();
void uart_string(char []);
void adc_init();
unsigned char getdata(unsigned char);
void uart_num(unsigned char);
unsigned char uart_read();


void main()
{
	DDRC=0x00;
	unsigned char digital;
	char value[];
	uart_init();
	//adc_init();
	_delay_ms(1000);
	uart_string("AT\r\n");
	_delay_ms(2000);
	uart_string("AT+CWMODE=1\r\n");
	_delay_ms(3000);
	
	

	uart_string("AT+CWJAP=\"tushar\",\"tushargarg18\"\r\n");
	_delay_ms(5000);
	_delay_ms(5000);
	_delay_ms(5000);


	while(1)
	{
		//digital=getdata(0x00);  // pin no.  // digital is a variable

		uart_string("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n"); // this for connected thingspeak network
		
		_delay_ms(3000);  // delay for n/w conncted


		uart_string("AT+CIPSEND=75\r\n");  // 51 byte of maximum data send
		_delay_ms(100);  // wait

		uart_string("GET https://api.thingspeak.com/update?api_key=Q3DOW9ESAGE0NK9X&field1=");  // particular address of my channel
		
		uart_num(digital);
		uart_string("\r\n");  // new line
		_delay_ms(1000);   // wait
		int k=0,i=0;
		uart_string("AT+CIPSEND=96");
		uart_string("GET https://api.thingspeak.com/channels/888289/feeds.json?api_key=SZW4V9R4PMKAQHWB&results=2\r\n");
		_delay_ms(2000);
		int num=0;
		value = uart_read();
		do
		{
			value[k] = uart_read();
			k++;
		}while(value[k] != '\0')
		
			if((i+5)<600 && value[i] == 'f' && value[i+1]=='i'&& value[i+2]=='i'&& value[i+3]=='e'&& value[i+4]=='l'&& value[i+5]=='d')
			{
				num = value[i+9]*100;
				num = num + value[i+10]*10;
				num=num+value[i+11];
			}
		}
			
	
		uart_string("AT+CIPCLOSE\r\n");   // connection close
		_delay_ms(6000);  // wait
	}
}


