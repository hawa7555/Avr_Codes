#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>
void adc_init();
void lcd_command(char );
void lcd_init(void );
void lcd_data_enable_to_write();
void lcd_command_enable_to_write();
void lcd_data(char );
void b2a(int );
int main()
{
  adc_init();
  lcd_init();
  while(1)
  {
    ADCSRA=ADCSRA|(1<<ADSC);
	while((ADCSRA&(1<ADIF))==0);
	b2a(ADC/4);
  }
}
void adc_init()
{
  DDRA=DDRA&~(1<<0);
  ADMUX=0xC0;//Vref=2.56V
  //ADMUX=0x00;//Aref
  ADCSRA=0xA7;
  //ADCSRA=0x87;
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
 _delay_ms(1);
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
