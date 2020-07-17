/*
 * Line_follow.c
 *
 * Created: 1/21/2019 8:39:53 PM
 *  Author: tushar
 */ 

#define F_CPU 14745600
#define TE  (1<<5)
#define right 0x02
#define left 0x01
#define mid	0x03
#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>

unsigned int left_sensor=0,right_sensor=0,middle_sensor=0;
void timer1_init_motor_count(void);
void timer2_init_motor_Speed(void);
void timer3_init_motor_count(void);
void adc_init(void);
void interupt_init(void);
void uart0_init(void);
unsigned int analogread(int);
void motor_init(void);
void uart_tx(char);
void initialise(void);
void motor_Speed(int,int);
void b2a(int);
void right_sixtydegree(void);
void left_sixtydegree(void);
void node_to_node(void);
int check_pos(void);

void timer2_init_motor_Speed()
{
	TCNT2=0 ;
	TCCR2A=TCCR2A|(1<<7);		//non inverting a
	TCCR2A=TCCR2A|(1<<5);		//non inverting b
	TCCR2A=TCCR2A|(3<<0);		//wgm0-1
	TCCR2B=TCCR2B|(1<<0);		//prescaler=1
	DDRB=DDRB|(1<<4);
	DDRH=DDRH|(1<<6);
	
}
void timer3_init_motor_count()
{
	DDRE=DDRE&~(1<<6);
	TCCR3A=0x00;
	TCCR3A=0x00;
	TCNT3H=0;
	TCNT3L=0;
	TCCR3B=0x06;
}
void timer1_init_motor_count()
{
	DDRD=DDRD&~(1<<6);
	TCCR1A=0x00;
	TCCR1C=0x00;
	TCNT1H=0;
	TCNT1L=0;
	TCCR1B=0x06;
	
}
void interupt_init()
{
	DDRD=DDRD&~(1<<0);
	EICRA=0x00;
	EIMSK=0b00000001;
}
void adc_init()
{
	ADMUX=0x00;
	ADCSRB=0x00;	//mux
	ADCSRA=0xA7;	//adc enable
	DDRF=DDRF&~(1<<1);
	DDRF=DDRF&~(1<<2);
	DDRF=DDRF&~(1<<3);
}
void uart0_init()
{
	UCSR0B = 0x00;							//disable while setting baud rate
	UCSR0A = 0x00;
	UCSR0C = 0x06;							//8 bit
	UBRR0L = 0x5F; 							//9600BPS at 14745600Hz
	UBRR0H = 0x00;
	UCSR0B = 0x08;
	//UCSR0C  = 3<<1;							//setting 8-bit character and 1 stop bit
	//UCSR0B = RX | TX;
}
unsigned int analogread(int inputpin)
{
	ADMUX=inputpin;
	ADCSRA=ADCSRA|(1<<ADSC);  //start conversion
	while((ADCSRA&(1<<ADIF))==0);
	ADCSRA=ADCSRA|(1<<ADIF);
	return ADC;
}
void motor_init()
{
	DDRA=DDRA|(15<<0);
	PORTA=PORTA&0xf0;
	motor_Speed(180,255);
}
void uart_tx(char data)
{

	while(!(UCSR0A & TE));                       //waiting to transmit
	UDR0 = data;
}
void initialise()
{
	timer1_init_motor_count();
	timer2_init_motor_Speed();
	timer3_init_motor_count();
	uart0_init();
	motor_init();
	adc_init();
	interupt_init();
}
void motor_Speed(int left_motor,int right_motor)
{
	OCR2A=right_motor;
	OCR2B=left_motor;
}
void b2a(int a)
{
	int a1,i;
	for(i=0;i<3;i++)
	{
		a1=a%10;
		a=a/10;
		uart_tx(a1+48);
	}
}
void right_sixtydegree()
{
	//sei();
	TCNT1=0;
	motor_Speed(180,255);
	while(TCNT1<=260)
	{
		PORTA=PORTA|(1<<2);
		PORTA=PORTA&~(1<<3);
		PORTA=PORTA|(1<<1);
		PORTA=PORTA&~(1<<0);
		left_sensor=analogread(left);
		right_sensor=analogread(right);
	}
	PORTA=PORTA&~(1<<0);
	PORTA=PORTA&~(1<<1);
	PORTA=PORTA&~(1<<2);
	PORTA=PORTA&~(1<<3);
	//cli();

}
void left_sixtydegree()
{
	//sei();
	TCNT1=0;
	motor_Speed(180,255);
	while(TCNT1<=260)
	{
		PORTA=PORTA|(1<<3);
		PORTA=PORTA&~(1<<2);
		PORTA=PORTA|(1<<0);
		PORTA=PORTA&~(1<<1);
	}
	PORTA=PORTA&~(1<<0);
	PORTA=PORTA&~(1<<1);
	PORTA=PORTA&~(1<<2);
	PORTA=PORTA&~(1<<3);
	//cli();
}
void node_to_node()
{
	//sei();
	motor_Speed(140,150);
	TCNT1=0;
	//int check;
	//int left_sensor,right_sensor;
	while(TCNT1<=750)
	{
			PORTA=PORTA|(1<<2);
			PORTA=PORTA&~(1<<3);
			PORTA=PORTA|(1<<0);
			PORTA=PORTA&~(1<<1);
			//check=check_pos();
			//if(check==1)
			//{
			//break;
			//}			
	}
	PORTA=PORTA&~(1<<0);
	PORTA=PORTA&~(1<<1);
	PORTA=PORTA&~(1<<2);
	PORTA=PORTA&~(1<<3);
	cli();
}
int check_pos()
{
	PORTA=PORTA|(1<<2);
	PORTA=PORTA&~(1<<3);
	PORTA=PORTA|(1<<0);
	PORTA=PORTA&~(1<<1);
	motor_Speed(0,0);
	
	//int temp=TCNT1;
	int flag=0;
	
	while(flag!=1)
	{
			left_sensor=analogread(left);
			right_sensor=analogread(right);
			middle_sensor=analogread(mid);
	if(left_sensor>=140 && right_sensor<=140 && middle_sensor<=140)
	{
		motor_Speed(120,165);
		flag=0;
	}
	if(left_sensor<=140 && right_sensor>=140 && middle_sensor<=140)
	{
		motor_Speed(140,140);
		flag=0;
	}
	if(left_sensor<=140 && right_sensor<=140 && middle_sensor>=140)
	{
		motor_Speed(140,165);
		flag=-1;
	}
	if(left_sensor>=140 && right_sensor>=140 && middle_sensor>=140)
	{
		motor_Speed(0,0);
		flag=1;
	}
	}	
	//motor_Speed(180,255);
	//TCNT1=temp;
}
ISR(INT0_vect)
{
	motor_Speed(0,0);
	int temp=TCNT1;
	//int left_sensor,right_sensor;
	//right_sensor=analogread(right);
	//left_sensor=analogread(left);
	//while(left_sensor>550 | right_sensor>550)
	//{
		if(left_sensor>550 && right_sensor<350)
		{
			//while(left_sensor>550)
			//{
			motor_Speed(160,255);
			b2a(left_sensor);
			b2a(right_sensor);
			left_sensor=analogread(left);
			right_sensor=analogread(right);
			//}			
			//_delay_ms(50);
		}
		else
		if (right_sensor>550 && left_sensor<350)
		{
			//while(right_sensor>550)
			//{
			motor_Speed(180,220);
			b2a(left_sensor);
			b2a(right_sensor);
			left_sensor=analogread(left);
			right_sensor=analogread(right);
			//}			
			//_delay_ms(50);
		}
	//}
	TCNT1=temp;
	motor_Speed(180,255);
	//while(1);
}

int main(void)
{
	initialise();
		check_pos();
	//for(int i=0;i<6;i++)
	//{	
	//node_to_node();
	//_delay_ms(200);
    //left_sixtydegree();
	/*_delay_ms(200);
	node_to_node();
	_delay_ms(200);
	right_sixtydegree();
	_delay_ms(200);
	node_to_node();
	_delay_ms(200);
	left_sixtydegree();
	*/
	//_delay_ms(200);
	//}
	/*while(1)
	{
	int a=analogread(0x01);
	int b=analogread(0x03);
	int c=analogread(0x02);
	b2a(a);
	b2a(b);
	b2a(c);	
	_delay_ms(1000);
	}*/	
}