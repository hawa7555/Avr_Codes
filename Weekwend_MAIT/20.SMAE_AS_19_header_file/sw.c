#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>
#include"defines.h"
int main()
{
 PA0_INPUT;PA1_INPUT;
 PC0_OUTPUT;PC1_OUTPUT;

  while(1)
  {
    if(SW0) 		LED0_ON;
	else if(SW1)    LED1_ON;
	else
	{
	  LED0_OFF;LED1_OFF;
	}
  }
}
