#define F_CPU 14745600
#include <avr/io.h>
#include <util/delay.h>
#define f 14745600

void timer_init()
{
	TCCR1A=0b10000011;
	TCCR1B=0b00011001;
	TCCR1C=0b00000000;
	TCNT1=0x00;
	//TCNT1L=0x00;
	//TIFR1=TIFR1|(1<<TOV1);
}

void servo(float degree)
{
	float t_high=1.5+((0.5*degree)/90);
	OCR1A=(int) f*(t_high/1000);
	
}

void main()
{
	DDRB=DDRB|(1<<4);
	timer_init();
	while(1)
	{
		OCR1A=57;
		_delay_ms(1000);
		OCR1A=9;
		_delay_ms(1000);
	}
	//while(1);
	//while(1)
	//{
		/*servo(90);
		_delay_ms(1000);
		servo(90);
		_delay_ms(1000);
		servo(-90);
		_delay_ms(1000);
		servo(-90);
		_delay_ms(1000);*/
		/*OCR1A=32000;
		_delay_ms(3000);
		OCR1A=32000;
		_delay_ms(3000);
		*/
	//}
	
}