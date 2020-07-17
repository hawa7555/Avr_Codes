#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>
#define Forward  0b00001010
#define Backward 0b00000101
#define Left 	 0b00000010
#define Right    0b00001000
#define Stop 	 0b00000000
#define BOT PORTA
int main()
{
	DDRC=DDRC &~ 0x0F;
	DDRA=DDRA | (0b00001111);
	int x;
	while(1)
	{
		x=PINC;
		x=x & 0x0F;
		switch(x)
		{
			case 2: BOT=Forward;break;
			case 4: BOT=Left;break;
			case 6: BOT=Right;break;
			case 8: BOT=Backward;break;
			case 5: BOT=Stop;break;
			default: BOT=Stop;
		}
	}
	return 0;
}
