#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>
int main()
{
    int i;
  DDRA=0b11111111;
  char x[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
  while(1)
  {
     for(i=0;i<=9;i++)
	 {
	  PORTA=x[i];
	  _delay_ms(300);
	 }
}
return 0;
}
