#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>
void i2c_start();
void i2c_SLA_W(char );
void i2c_data(char );
void i2c_stop();
void uart_init();
void tx_string(char *);
int main()
{
  int i;
  uart_init();
  i2c_start();
  i2c_SLA_W(0x40);
  for(i=0;i<=7;i++)
  {
    i2c_data(1<<i);
  }
  i2c_stop();
}
void uart_init()
{
 UBRRL=0x33;//Fosc=8Mhz,BR=9600
 UCSRB=UCSRB|(1<<TXEN);
 UCSRC=UCSRC|(1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);

}
void tx_string(char *x)
{
 while(*x)
 {
   UDR=*x++;
   _delay_ms(100);
 }
}
void i2c_start()
{
  TWBR=8;
  TWCR=TWCR|(1<<TWINT)|(1<<TWEN)|(1<<TWEA)|(1<<TWSTA);
  while( (TWCR&(1<<TWINT))==0);
  switch(TWSR)
  {
   case 0x08:tx_string("A START condition has been transmitted\r"); break;
   case 0x10:tx_string("A repeated START condition has been transmitted\r");break;
   default: tx_string("ERROR in Start Condition\r");
   
  }

}
void i2c_SLA_W(char x)
{
  TWDR=x;
  TWCR=TWCR|(1<<TWINT)|(1<<TWEN)|(1<<TWEA);
  while( (TWCR&(1<<TWINT))==0);
  switch(TWSR)
 {
  case 0x18:tx_string("SLA+W has been transmitted; ACK has been received\r"); break;
  case 0x20:tx_string("SLA+W has been transmitted;NOT ACK has been received\r");break;
  default: tx_string("ERROR in SLA+W \r");
 }

 
}
void i2c_data(char x)
{
  TWDR=x;
  TWCR=TWCR|(1<<TWINT)|(1<<TWEN)|(1<<TWEA);
  while( (TWCR&(1<<TWINT))==0);
  switch(TWSR)
 {
  case 0x28:tx_string("Data byte has been transmitted;ACK has been received\r"); break;
  case 0x30:tx_string("Data byte has been transmitted;NOT ACK has been received\r");break;
  default: tx_string("ERROR in DATA Write\r");
 }  

}
void i2c_stop()
{
   TWCR=TWCR|(1<<TWINT)|(1<<TWEN)|(1<<TWEA)|(1<<TWSTO);
 
}
