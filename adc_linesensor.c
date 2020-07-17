/*
 * adc_linesensor.c
 *
 * Created: 1/21/2019 12:26:26 PM
 *  Author: tusha
 */ 


#include <avr/io.h>
#define RX  (1<<4)
#define TX  (1<<3)
#define TE  (1<<5)
#define RE  (1<<7)

void uart0_init()
{
	UCSR0B = 0x00;							//disable while setting baud rate
	UCSR0A = 0x00;
	UCSR0C = 0x06;							//8 bit
	UBRR0L = 0x5F; 							//9600BPS at 14745600Hz
	UBRR0H = 0x00;
	UCSR0B = 0x98;
	//UCSR0C  = 3<<1;							//setting 8-bit character and 1 stop bit
	//UCSR0B = RX | TX;
}


void uart_tx(char data)
{

	while(!(UCSR0A & TE));                       //waiting to transmit
	UDR0 = data;
}


int main(void)
{
	
	adc_init();
	uart0_init();
	ADMUX=ADMUX|(1<<0);
	DDRF=DDRF&~(1<<1);
	while(1)
    {	
		ADCSRA=ADCSRA|(1<<6);
		while(!ADCSRA&(1<<ADIF));
		uart_tx(ADC);
		ADCSRA=ADCSRA|(1<<ADIF);
        //TODO:: Please write your application code 
    }
}
adc_init()
{
	ADMUX=ADMUX|(1<<6);		//ref 5 volt
	ADMUX=ADMUX|(1<<7);	//ref 5 volt
	ADMUX=ADMUX&~(1<<5);	//lower bit in 8
	ADMUX=ADMUX&~(31<<0);	//mux select
	ADCSRB=ADCSRB&~(1<<3);	//mux
	ADCSRA=ADCSRA|(1<<7);	//adc enable
		
}