#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

#define row0 0
#define row1 1
#define row2 2
#define row3 3
#define col0 4
#define col1 5
#define col2 6
#define col3 7

void keypad();
void lcd_cmd(char);
void lcd_cmd_enable();
void lcd_data(char);
void lcd_data_enable();
void lcd_display(char []);

void keypad()
{
	PORTA=PORTA&~(1<<col0);
    PORTA=PORTA|(1<<col1)|(1<<col2)|(1<<col3);
	if( (PINA&(1<<row0))==0 )
	{
		lcd_cmd(0x01);
		lcd_display("Key 7 is pressed");
	 }
	
	else if( (PINA&(1<<row1))==0 )
	 {
		lcd_cmd(0x01);
		lcd_display("Key 4 is pressed");
	  }
    
	else if( (PINA&(1<<row2))==0 )
   {
	 lcd_cmd(0x01);
	 lcd_display("Key 1 is pressed");
    }
   
   else if( (PINA&(1<<row3))==0 )
    {
	  lcd_cmd(0x01);
	  lcd_display("Key ON is pressed");
     }

 PORTA=PORTA&~(1<<col1);
 PORTA=PORTA|(1<<col0)|(1<<col2)|(1<<col3);
 
 if( (PINA&(1<<row0))==0 )
 {
	lcd_cmd(0x01);
	lcd_display("Key 8 is pressed");
  }
 
 else if( (PINA&(1<<row1))==0 )
 {
	lcd_cmd(0x01);
	lcd_display("Key 5 is pressed");
 }
 
 else if( (PINA&(1<<row2))==0 )
 {
	lcd_cmd(0x01);
	lcd_display("Key 2 is pressed");
 }
 
 else if( (PINA&(1<<row3))==0 )
 {
	lcd_cmd(0x01);
	lcd_display("Key 0 is pressed");
 }
 
    PORTA=PORTA&~(1<<col2);
    PORTA=PORTA|(1<<col0)|(1<<col1)|(1<<col3);
    
	if( (PINA&(1<<row0))==0 )
    {
	    lcd_cmd(0x01);
	    lcd_display("Key 9 is pressed");
    }
    
	else if( (PINA&(1<<row1))==0 )
    {
	    lcd_cmd(0x01);
	    lcd_display("Key 6 is pressed");
    }
    
	else if( (PINA&(1<<row2))==0 )
    {
	    lcd_cmd(0x01);
	    lcd_display("Key 3 is pressed");
    }
    
	else if( (PINA&(1<<row3))==0 )
    {
	    lcd_cmd(0x01);
	    lcd_display("Key = is pressed");
    }
	
	PORTA=PORTA&~(1<<col3);
	PORTA=PORTA|(1<<col0)|(1<<col1)|(1<<col2);
	
	if( (PINA&(1<<row0))==0 )
	{
		lcd_cmd(0x01);
		lcd_display("Key / is pressed");
	}
	
	else if( (PINA&(1<<row1))==0 )
	{
		lcd_cmd(0x01);
		lcd_display("Key * is pressed");
	}
	
	else if( (PINA&(1<<row2))==0 )
	{
		lcd_cmd(0x01);
		lcd_display("Key - is pressed");
	}
	
	else if( (PINA&(1<<row3))==0 )
	{
		lcd_cmd(0x01);
		lcd_display("Key + is pressed");
	}
}

   void lcd_cmd(char x)
   {
	   PORTC=x&(0xF0);
	   lcd_cmd_enable();
	   PORTC=(x<<4)&(0xF0);
	   lcd_cmd_enable();
     }
  
  void lcd_cmd_enable()
  {
	   PORTC=PORTC&~(1<<0);   //RS=0
	   PORTC=PORTC&~(1<<1);   //RW=0
	   PORTC=PORTC|(1<<2);    //EN=1
	   PORTC=PORTC&~(1<<2);   //EN=0
	   _delay_ms(1);
    }
 
 void init()
 {
	 DDRC=0xFF;
	 lcd_cmd(0x02);
	 lcd_cmd(0x28);
	 lcd_cmd(0x0E);
	 //lcd_cmd(0x01);
	 //lcd_cmd(0x06);
	 lcd_cmd(0x80);
   }
  
  void lcd_data(char x)
  {
	  PORTC=x&(0xF0);
	  lcd_data_enable();
	  PORTC=(x<<4)&(0xF0);
	  lcd_data_enable();
  }
  
  void lcd_data_enable()
  { 
	  PORTC=PORTC|(1<<0);    //RS=1
	  PORTC=PORTC&~(1<<1);   //RW=0
	  PORTC=PORTC|(1<<2);    //EN=1
	  PORTC=PORTC&~(1<<2);   //EN=0
	  _delay_ms(1);
    }
	
void lcd_display(char a[])
{
	for(int i=0;a[i]!='\0';i++)
	{
		lcd_data(a[i]);
		//_delay_ms(300);
		_delay_ms(50);
	}
  }
	
 void main()
 {
	 PORTA=0x0F;      //just pull up activation
	 DDRA=0xF0;
	 init();
	 while(1)
	 {
		keypad();
	  }
  }
  