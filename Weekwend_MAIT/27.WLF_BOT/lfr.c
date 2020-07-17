#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>
#define Forward 0b01010101
#define Backward 0b10101010
#define Left 0b01010000
#define Right 0b00000101
#define Stop 0b00000000
#define BOT PORTA
#define ls (PINC&(1<<0))
#define rs (PINC&(1<<1))
int main()
{
  DDRA= 0b11111111;
  DDRC=DDRC&~((1<<0)|(1<<1));
  while(1)
  {
   	if(ls && rs)
   	{
    	BOT=Forward;
   	}
   if( !(ls) && (rs))
   {
    	BOT=Stop;_delay_ms(2000);
		BOT=Left;
   }
   if((ls) && !(rs) )
   {
    	BOT=Stop;_delay_ms(2000);
     	BOT=Right;
   }
  if( !(ls) && !(rs))
 	 {
    	 BOT=Stop;
  	 } 

  }
}
