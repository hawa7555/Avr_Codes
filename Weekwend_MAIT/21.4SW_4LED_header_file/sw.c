#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>
#include"xyz.h"
int main()
{
 PA0_INPUT;PA1_INPUT;PA2_INPUT;PA3_INPUT;
 PC0_OUTPUT;PC1_OUTPUT;PC2_OUTPUT;PC3_OUTPUT;

  while(1)
  {
    if(SW0) 		LED0_ON;
	else if(SW1)    LED1_ON;
	else if(SW2)    LED2_ON;
	else if(SW3)    LED3_ON;
	else
	{
	  LED0_OFF;LED1_OFF;LED2_OFF;LED3_OFF;
	}
  }
}
