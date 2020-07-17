#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>
void counter_init();
void lcd_command(char );
void lcd_init(void );
void display();
void lcd_data_enable_to_write();
void lcd_command_enable_to_write();
void lcd_data(char );
void b2a(int );
int main()
{
 lcd_init();
 counter_init();
 while(1)
 {
  do
  {
	b2a(TCNT0);
  }
  while((TIFR&(1<<TOV0))==0);
 }
}
void b2a(int a)//254
{
  char pos=0x85;
  int a1,i;
  for(i=0;i<6;i++)//0//1//2
  {
  	a1=a%10;//4//5//2
  	a=a/10;//25//2//0
  	lcd_command(pos);
  	lcd_data(a1+48);//'4'//'5'//'2'
  	pos--;//81//80
  }
}
void counter_init()
{

 DDRB=DDRB&~(1<<0);
 TCNT0=0;//0!='0'
 TCCR0=0x06;
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
 _delay_ms(1);
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
