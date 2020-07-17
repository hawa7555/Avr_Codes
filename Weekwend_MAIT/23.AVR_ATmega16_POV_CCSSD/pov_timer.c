#define F_CPU 1000000UL
#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>
char a[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
int i,j,k;

ISR(TIMER0_OVF_vect)
{
  PORTB=0b11111101;
  TCNT0=0;

}
void timer0_int_init()
{
  
   
   TIMSK=TIMSK|(1<<0);
   sei();
}
int main()
{
   DDRB=DDRA=0xff;
   timer0_int_init();
    TCCR0=0x05;
   while(1)
   {
      for(i=0;i<=9;i++)
	  {
	    for(j=0;j<=9;j++)
		{
		  for(k=0;k<=49;k++)
		  {
		    
			PORTA=a[i];
			//_delay_ms(10);
			PORTB=0b11111110;
			PORTA=a[j];
			//_delay_ms(10);

		  }
	  }
   }
}
return 0;
}
