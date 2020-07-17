#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>
void uart_init(void);
void tx_string(char *);
int main()
{
	DDRB=DDRB&~(0x0F);
	uart_init();
	int x=PINB;
	//x=x&0x0F;
	/*switch(x)
	{
		case 1: tx_string("Text number 1");
		        break;
		case 2:  tx_string("Text number 2");
		         break;
		case 3:  tx_string("Text number 3");
		          break;
		case 4:  tx_string("Text number 4");
		          break;
	}*/
while(1)
{
if(x&(1<<0))
{
   	//while(x&(1<<0))
	   {
	   tx_string("Text String 1");
	   }
}
else if(x&(1<<1))
{
	tx_string("Text String 2");
}
else if(x&(1<<2))
{
	tx_string("Text String 3");
}
else if(x&(1<<3))
{
	tx_string("Text String 4");
}

}
	}
void tx_string(char *x)//2000
{
	while(*x != '\0')
	{
		UDR=*x++;
		while( (UCSRA&(1<<5))==0);//wait here till UDRE is 0
		_delay_ms(100);
	}

}
void uart_init()
{
	UBRRL=0x33;//Fosc=8Mhz,BR=9600
	UCSRB=UCSRB|(1<<TXEN);
	UCSRC=UCSRC|(1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);

}