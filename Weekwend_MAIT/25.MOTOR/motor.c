#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>
int main()
{
  DDRA= 0b11111111;
  while(1)
  {
  	PORTA=0b01010101;
  	_delay_ms(1000);
  	PORTA=0b10101010;
  	_delay_ms(1000);
  }
}
