#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>
char a[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
int i,j,k;
int main()
{
   DDRB=DDRA=0xff;
   while(1)
   {
      for(i=0;i<=9;i++)
	  {
	    for(j=0;j<=9;j++)
		{
		  for(k=0;k<100;k++)
		  {

		    	PORTB=0b11111110;//ssd0 Select,ssd1 deselect
				PORTA=a[i];
				_delay_ms(5);
				PORTB=0b11111101;//ssd1 select ,ssd0 deselect
				PORTA=a[j];
				_delay_ms(5);

		  }
	  }
   }
}
return 0;
}
