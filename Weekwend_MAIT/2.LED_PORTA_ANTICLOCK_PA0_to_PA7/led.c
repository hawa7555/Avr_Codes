
#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>
int main()
{
  DDRA=0b11111111;
  while(1)
  {
    PORTA=0b00000001;//0x01//1//(1<<0)
	_delay_ms(100);
	PORTA=0b00000010;//0x02//2//(1<<1)
	_delay_ms(100);
	PORTA=0b00000100;//0x04//4//(1<<2)
	_delay_ms(100);
	PORTA=0b00001000;//0x08//8//(1<<3)
	_delay_ms(100);
	PORTA=0b00010000;//0x010//16//(1<<4)
	_delay_ms(100);
	PORTA=0b00100000;//0x20//32//(1<<5)
	_delay_ms(100);
	PORTA=0b01000000;//0x40//64//(1<<6)
	_delay_ms(100);
	PORTA=0b10000000;//0x80//128//(1<<7)
	_delay_ms(100);
  }
return 0;
}


