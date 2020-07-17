#define F_CPU 1000000UL
#include<avr/io.h>
#include<util/delay.h>

void main()
{
	DDRA=0xFF;
	DDRB=DDRB|(3<<0);
	char a[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x6F,0x7F};
	while(1)
	{
	  for(int i=0;i<10;i++)
	  {
		  for(int j=0;j<10;j++)
		  {
			  for(int k=0;k<100;k++)
			  {
				  PORTB=0b11111110;
				  PORTA=a[i];
				  _delay_ms(5);
				  
				  PORTB=0b11111101;
				  PORTA=a[j];
				  _delay_ms(5);
			  }
		   }
	  }
	}
}