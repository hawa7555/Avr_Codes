#define F_CPU 1000000UL
#include<avr/io.h>
void delay(void);
int main()
{
  DDRA=DDRA|(1<<PA0);
  while(1)
  {
    PORTA=PORTA|(1<<0);
	delay();
	PORTA=PORTA&~(1<<0);
	delay();

  }
}
void delay()
{
  TCNT0=246;
  TCCR0=0x01;
  while((TIFR&(1<<TOV0))==0);//wait here
  TIFR=TIFR | (1<<TOV0);//cle flag by writing 1 on it
}
