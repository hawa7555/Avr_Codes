#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>
void lcd_command(char );
void lcd_init(void );
void display();
void lcd_data_enable_to_write();
void lcd_command_enable_to_write();
void lcd_data(char );
int main()
{
  lcd_init();
  while(1)
  {
    
    display();
	lcd_command(0x01);


  }
return 0;
}


void display()
{
 char a[]="GOD IS ONE";
 char b[]="BUT WHO BELIEVS";
 int i;

 lcd_command(0x80);
 for(i=0;a[i] != '\0'; i++)
 {
  lcd_data(a[i]);
  _delay_ms(100);
 }

 lcd_command(0xC0);
 for(i=0;b[i] != '\0'; i++)
 {
  lcd_data(b[i]);
  _delay_ms(100);
 }
}
void lcd_init()
{
    DDRA=0xff;
	lcd_command(0x02);
    lcd_command(0x28);
	lcd_command(0x0E);

}
void lcd_command(char x)
{
 PORTA=(x&0xf0);  //upper 4 bit
 lcd_command_enable_to_write();
 PORTA=((x<<4)&0xf0); //lower 4 bit
 lcd_command_enable_to_write();
}
void lcd_data(char x)
{
 PORTA=(x&0xf0);  //upper 4 bit
 lcd_data_enable_to_write();
 PORTA=((x<<4)&0xf0); //lower 4 bit
 lcd_data_enable_to_write();
}
void lcd_data_enable_to_write()
{
 PORTA=PORTA |(1<<0);//RS=0;
 PORTA=PORTA&~(1<<1);//RW=0;
 PORTA=PORTA |(1<<2);//EN=1;
 PORTA=PORTA&~(1<<2);//EN=0;
 _delay_ms(1);
}

void lcd_command_enable_to_write()
{
 PORTA=PORTA&~(1<<0);//RS=0;
 PORTA=PORTA&~(1<<1);//RW=0;
 PORTA=PORTA |(1<<2);//EN=1;
 PORTA=PORTA&~(1<<2);//EN=0;
 _delay_ms(1);
}
