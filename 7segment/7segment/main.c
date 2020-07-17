#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>

void main()
{
	DDRA=0xFF;
	DDRB=0xFF;
	char x[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
	char a[10]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90}; 
	 while(1)
	 {
	   for(int i=0;i<10;i++)
	 {
		//PORTB=0b
		for(int j=0;j<10;j++)
		{
		 for(int k=0;k<100;k++)
		 {
	     PORTB=0b00000011;
		 PORTA=a[i];
		 _delay_ms(5);
		 PORTB=0b00000000;
		 PORTA=x[j];
		 _delay_ms(5);
	    }
	  }
	 }
  }
}