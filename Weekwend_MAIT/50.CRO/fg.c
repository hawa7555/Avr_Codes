#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>
void adc_init();
void pwm_init();
void send2ocr(int );
int main()
{
  adc_init();
  pwm_init();
  while(1)
  {
    ADCSRA=ADCSRA|(1<<ADSC);
	while((ADCSRA&(1<ADIF))==0);
	send2ocr(ADC);
  }
}
void pwm_init()
{
    DDRB=DDRB|(1<<PB3);
  	TCNT0=0;
  	TCCR0=0x69;
}
void send2ocr(int x)
{
 OCR0=x;
}
void adc_init()
{
  DDRA=DDRA&~(1<<0);
  ADMUX=0xC0;//Vref=2.56V
  //ADMUX=0x00;//Aref
  ADCSRA=0xA7;
  //ADCSRA=0x87;
}
