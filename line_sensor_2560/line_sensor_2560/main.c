#define F_CPU 14745600
#include <avr/io.h>
#include <util/delay.h>

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
void adc_init()
{
	ADMUX=ADMUX|(1<<6);		//ref 5 volt
	ADMUX=ADMUX|(1<<7);	//ref 5 volt
	ADMUX=ADMUX&~(1<<5);	//lower bit in 8
	ADMUX=ADMUX&~(31<<0);	//mux select
	ADCSRB=ADCSRB&~(1<<3);	//mux
	ADCSRA=ADCSRA|(1<<7);	//adc enable
	
}
void b2a(int a)
{
	//char pos=0x85;
	int a1,i;
	for(i=0;i<3;i++)
	{
		a1=a%10;
		a=a/10;
		uart_tx(a1+48);
		//pos--;
	}
}


int main(void)
{
	DDRF=DDRF&~(14<<0);
	adc_init();
	uart0_init();
	//ADMUX=ADMUX|(1<<0);
	DDRF=DDRF&~(1<<1);
	while(1)
	{
		ADMUX=ADMUX|(1<<0);    //adc1
		ADCSRA=ADCSRA|(1<<6);  //start conversion
		while(!(ADCSRA&(1<<ADIF)));
		//uart_tx(ADC);
		b2a(ADC);
		ADCSRA=ADCSRA|(1<<ADIF);  //clearing flag
		_delay_ms(100);
		
		ADMUX=ADMUX|(1<<1);   //adc2
		ADMUX=ADMUX&~(1<<0);  //adc2
		ADCSRA=ADCSRA|(1<<6);  //start conversion
		while(!(ADCSRA&(1<<ADIF)));
		b2a(ADC);
		ADCSRA=ADCSRA|(1<<ADIF);  //clearing flag
		_delay_ms(100);
		
		ADMUX=ADMUX|(3<<0);   //adc3
		ADCSRA=ADCSRA|(1<<6);  //start conversion
		while(!(ADCSRA&(1<<ADIF)));
		b2a(ADC);
		ADCSRA=ADCSRA|(1<<ADIF);  //clearing flag
		_delay_ms(100);
	}
}

