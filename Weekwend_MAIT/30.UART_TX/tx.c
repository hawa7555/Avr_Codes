/*
#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>
void uart_init(void);
void tx(char );
int main()
{
 uart_init();
 while(1)
 {
  tx('A');
  tx('B');
 }
return 0;
}
void tx(char x)
{
  UDR=x;
  while( (UCSRA&(1<<5))==0);//wait here till UDRE is 0
}
void uart_init()
{
 UBRRL=0x33;//Fosc=8Mhz,BR=9600
 UCSRB=UCSRB|(1<<TXEN);
 UCSRC=UCSRC|(1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);

}
*/
#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>
void uart_init(void);
void tx_string(char *);
int main()
{
 uart_init();
 while(1)
 {
  tx_string("RAJA HINDUSTANI\r");
 }
return 0;
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




















