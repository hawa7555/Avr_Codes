#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>

void i2c_init();
void mt_mode();
void data_lcd();
void data_send(char);
void cmd_lcd();
void cmd_send(char);
void transmit();

void i2c_init()
{
	TWBR=8;
	TWCR=TWCR|(1<<TWSTA)|(1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	while((TWCR&(1<<TWINT))==0);
	//TWCR=TWCR|(1<<TWINT);
	//if(TWSR==0x08) return;
	//else i2c_init();
}

void mt_mode()
{
	TWDR=0x40;     //slave address
	TWCR=TWCR|(1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	while((TWCR&(1<<TWINT))==0);
	//TWCR=TWCR|(1<<TWINT);
	//if(TWSR==0x18) return;
	//else mt_mode();
}

void data_send(char x)
{
	TWDR=x&(0xF0);
	transmit();
	data_lcd();
	transmit();
	TWDR=(x<<4)&(0xF0);
	transmit();
	data_lcd();
	transmit();
}

void data_lcd()
{
	TWDR=TWDR|(1<<0);   //rs=1
	TWDR=TWDR&~(1<<1);  //rw=0
	TWDR=TWDR|(1<<2);   //en=1
	transmit();
	_delay_ms(10);
	TWDR=TWDR&~(1<<2);  //en=0;
}

void transmit()
{
	TWCR=TWCR|(1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	while((TWCR&(1<<TWINT))==0);
	//TWCR=TWCR|(1<<TWINT);
}

void cmd_lcd()
{
	TWDR=TWDR&~(1<<0);   //rs=0
	TWDR=TWDR&~(1<<1);  //rw=0
	TWDR=TWDR|(1<<2);   //en=1
	transmit();
	_delay_ms(10);
	TWDR=TWDR&~(1<<2);  //en=0;
}

void cmd_send(char x)
{
	TWDR=x&(0xF0);
	transmit();
	cmd_lcd();
	transmit();
	TWDR=(x<<4)&(0xF0);
	transmit();
	cmd_lcd();
	transmit();
}

void lcd_init()
{
	cmd_send(0x02);
	cmd_send(0x28);
	cmd_send(0x01);
	cmd_send(0x0E);
	cmd_send(0x80);
}

void main()
{
	i2c_init();
	mt_mode();
	lcd_init();
	int i=20;
	while(i!=0)
	{
		cmd_send(0x01);
		cmd_send(0x80);
		data_send('H');
		_delay_ms(100);
		data_send('W');
		_delay_ms(1000);
		i--;
	}
	TWCR=TWCR|(1<<TWINT)|(1<<TWEN)|(1<<TWEA)|(1<<TWSTO);
}