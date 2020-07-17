#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>
#define row0 0
#define row1 1
#define row2 2
#define row3 3
#define col0 4
#define col1 5
#define col2 6
#define col3 7
void lcd_command(char );
void lcd_init(void );	
void lcd_data_enable_to_write();
void lcd_command_enable_to_write();
void lcd_data(char );
void lcd_string(const char *);
void keypad();


int main()
{
   PORTA=0x0F;//activate pull up from PA0 to PA3
   DDRA=0xF0;
   lcd_init();
   while(1)
   {
    keypad();
   }

}
void keypad()
{
  PORTA=PORTA&~(1<<col0);
   PORTA=PORTA|(1<<col1)|(1<<col2)|(1<<col3);

   if( (PINA&(1<<row0))==0)
   {
    lcd_command(0x01);
    lcd_string("Key 7 Is pressed");
   }
   else if( (PINA&(1<<row1))==0)
   {
    lcd_command(0x01);
    lcd_string("Key 4 Is pressed");
   }
   else if( (PINA&(1<<row2))==0)
   {
    lcd_command(0x01);
    lcd_string("Key 1 Is pressed");
   }
   else if( (PINA&(1<<row3))==0)
   {
    lcd_command(0x01);
    lcd_string("Key ON/OF Is pressed");
   }

   PORTA=PORTA&~(1<<col1);
   PORTA=PORTA|(1<<col0)|(1<<col2)|(1<<col3);
   if( (PINA&(1<<row0))==0)
   {
    lcd_command(0x01);
    lcd_string("Key 8 Is pressed");
   }
   else if( (PINA&(1<<row1))==0)
   {
    lcd_command(0x01);
    lcd_string("Key 5 Is pressed");
   }
   else if( (PINA&(1<<row2))==0)
   {
    lcd_command(0x01);
    lcd_string("Key 2 Is pressed");
   }
   else if( (PINA&(1<<row3))==0)
   {
    lcd_command(0x01);
    lcd_string("Key 0 Is pressed");
   }

   PORTA=PORTA&~(1<<col2);
   PORTA=PORTA|(1<<col0)|(1<<col1)|(1<<col3);
   if( (PINA&(1<<row0))==0)
   {
    lcd_command(0x01);
    lcd_string("Key 9 Is pressed");
   }
   else if( (PINA&(1<<row1))==0)
   {
    lcd_command(0x01);
    lcd_string("Key 6 Is pressed");
   }
   else if( (PINA&(1<<row2))==0)
   {
    lcd_command(0x01);
    lcd_string("Key 3 Is pressed");
   }
   else if( (PINA&(1<<row3))==0)
   {
    lcd_command(0x01);
    lcd_string("Key = Is pressed");
   }
   
   PORTA=PORTA&~(1<<col3);
   PORTA=PORTA|(1<<col0)|(1<<col1)|(1<<col2);
   if( (PINA&(1<<row0))==0)
   {
    lcd_command(0x01);
    lcd_string("Key / Is pressed");
   }
   else if( (PINA&(1<<row1))==0)
   {
    lcd_command(0x01);
    lcd_string("Key * Is pressed");
   }
   else if( (PINA&(1<<row2))==0)
   {
    lcd_command(0x01);
    lcd_string("Key - Is pressed");
   }
   else if( (PINA&(1<<row3))==0)
   {
    lcd_command(0x01);
    lcd_string("Key + Is pressed");
   }
}
void lcd_string(const char *x)//x=2000
{
  
  while(*x !=  '\0')
  {
    lcd_data(*x++);
	_delay_ms(100);
	//x++; //2001//2002
  }

}
void lcd_init()
{
    DDRD=0xff;
	lcd_command(0x02);
    lcd_command(0x28);
	lcd_command(0x0E);

}
void lcd_command(char x)
{
 PORTD=(x&0xf0);  //upper 4 bit
 lcd_command_enable_to_write();
 PORTD=((x<<4)&0xf0); //lower 4 bit
 lcd_command_enable_to_write();
}
void lcd_data(char x)
{
 PORTD=(x&0xf0);  //upper 4 bit
 lcd_data_enable_to_write();
 PORTD=((x<<4)&0xf0); //lower 4 bit
 lcd_data_enable_to_write();
}
void lcd_data_enable_to_write()
{
 PORTD=PORTD |(1<<0);//RS=0;
 PORTD=PORTD&~(1<<1);//RW=0;
 PORTD=PORTD |(1<<2);//EN=1;
 PORTD=PORTD&~(1<<2);//EN=0;
 _delay_ms(1);
}

void lcd_command_enable_to_write()
{
 PORTD=PORTD&~(1<<0);//RS=0;
 PORTD=PORTD&~(1<<1);//RW=0;
 PORTD=PORTD |(1<<2);//EN=1;
 PORTD=PORTD&~(1<<2);//EN=0;
 _delay_ms(1);
}
