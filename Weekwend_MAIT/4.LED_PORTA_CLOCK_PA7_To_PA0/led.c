
#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>
int main()
{
 int i;
  DDRA=0b11111111;
  while(1)
  {
   for(i=7;i>=0;i--)
   {
    PORTA=(1<<i);
	_delay_ms(100);
   }
  }
return 0;
}
