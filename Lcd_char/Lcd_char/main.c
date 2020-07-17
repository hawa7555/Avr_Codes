#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
 void lcd_cmd(char x)
 {
	 PORTA=x;
	 PORTB=PORTB&~(1<<0);  //RS=0
	 PORTB=PORTB&~(1<<1);  //RW=0
	 PORTB=PORTB|(1<<2);   //EN=1
	 PORTB=PORTB&~(1<<2);  //EN=0
	 _delay_ms(1);
 }
 void init()
 {
	 DDRA=0xFF;
	 DDRB=DDRB|7;
	 lcd_cmd(0x38);
	 lcd_cmd(0x06);
	 lcd_cmd(0x0E);
	 lcd_cmd(0x01);
	 lcd_cmd(0x80);
	 
 }
 void lcd_data(char x)
 {
   PORTA=x;
   PORTB=PORTB|(1<<0);     //RS=1
   PORTB=PORTB&~(1<<1);    //RW=0
   PORTB=PORTB|(1<<2);     //EN=1
   PORTB=PORTB&~(1<<2);    //EN=0
   _delay_ms(1);
  
 }
 void display()
 {
   char a[]="LOADED....";
   for(int i=0;a[i]!='\0';i++)
   {
	   lcd_data(a[i]);
	   _delay_ms(100); 
   }
 }
 void main()
 {
	 init();
	 display();
	 lcd_data('254');
 }