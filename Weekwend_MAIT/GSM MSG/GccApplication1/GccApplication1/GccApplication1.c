#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
void txstring(char *);
void usart_init();
void gsm();
int main()
{
	DDRA=0x00;
	DDRB=0x01;
   usart_init();
   while(1)
   {
	   if(PINA&0x01)
	   {
            gsm();
			PORTB=0x01;
	   }	
	   else
	   PORTB=0x00;

   	
   }
return 0;
}
void txstring(char *x)
{
  while(*x)
  {
  	UDR=*x;
  	while( (UCSRA&(1<<UDRE))==0){}
    x++;
	_delay_ms(100);
  }
}
void usart_init()
{
	UCSRB=UCSRB|(1<<TXEN);
	UCSRC=UCSRC|(1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);
	UBRRL=0x33;
}

   void gsm()
{
   char ctrlz[]={26};
txstring("AT+CMGF=1\r");
_delay_ms(500);
txstring("AT+CMGS=\"8700070981\"\r");
_delay_ms(2000);
txstring("HELLOOOO");
_delay_ms(200);
txstring(ctrlz);

}
