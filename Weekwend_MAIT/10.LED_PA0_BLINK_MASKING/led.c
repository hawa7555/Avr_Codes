#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>
int main()
{
 DDRA=DDRA|(1<<0);
  while(1)
  {
    PORTA=PORTA|(1<<0);
    _delay_ms(500);
	PORTA=PORTA&~(1<<0);
	_delay_ms(500);
  }
return 0;
}
