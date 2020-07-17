#define F_CPU 14745600
#include <avr/io.h>
#include <util/delay.h>

int left_sensor;
int right_sensor;
int mid_sensor;
int prev_error=0;
int error=0;

void adc_init()
{
	ADMUX=0xc0;
	ADCSRB=0x00;	//mux
	ADCSRA=0xA7;	//adc enable
	DDRF=DDRF&~(1<<1);
	DDRF=DDRF&~(1<<2);
}

void motor_init()
{
	DDRA=DDRA|(15<<0);
	PORTA=PORTA&0xf0;
	motor_Speed(180,255);
}

void motor_Speed(int left,int right)
{
	OCR2A=right;
	OCR2B=left;
}

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


void read_sensor()
{
	//ADMUX=ADMUX|(1<<0);    //adc1
	ADMUX=0x01;
	ADCSRA=ADCSRA|(1<<6);  //start conversion
	while(!(ADCSRA&(1<<ADIF)));
	left_sensor=ADC;
	
	//ADMUX=ADMUX|(1<<1);   //adc2
	//ADMUX=ADMUX&~(1<<0);  //adc2
	ADMUX=0x02;
	ADCSRA=ADCSRA|(1<<6);  //start conversion
	while(!(ADCSRA&(1<<ADIF)));
	right_sensor=ADC;
	
	//ADMUX=ADMUX|(3<<0);   //adc3
	ADMUX=0x03;
	ADCSRA=ADCSRA|(1<<6);  //start conversion
	while(!(ADCSRA&(1<<ADIF)));
	mid_sensor=ADC;
}

void straight()
{
	motor_Speed(180,255);
	PORTA=PORTA|(1<<0);   //left motor forward
	PORTA=PORTA&~(1<<1);
	
	PORTA=PORTA|(1<<2);    //right motor forward
	PORTA=PORTA&~(1<<3);
}

void left()
{
	motor_Speed(180,255);
	do
	{
		PORTA=PORTA|(1<<1);     //left motor backward
		PORTA=PORTA&~(1<<0);
		
		PORTA=PORTA|(1<<2);    //right motor forward
		PORTA=PORTA&~(1<<3);
	}while(left_sensor>500);

}
void right()
{
	motor_Speed(180,255);
	//read_sensor();
	do
	{
		PORTA=PORTA|(1<<0);     //left motor forward
		PORTA=PORTA&~(1<<1);
		
		PORTA=PORTA|(1<<3);    //right motor backward
		PORTA=PORTA&~(1<<2);
		read_sensor();
	 }while(right_sensor>550);
}

void correction(int error)
{
	int correct;
	int left_speed,right_speed;
	float kp,ki,kd;
	correct=kp*error+kd*(error-prev_error)+ki*();
	
	left_speed=160+correct;
	right_speed=230-correct;
	
	if(left_speed>180)
	{
	  left_speed=180;
	}
	else if(left_speed<0)
	{
		left_speed=0;
	}
	
	
	if(right_speed>255)
	{
		right_speed=255;
	}
	else if(right_speed<0)
	{
		right_speed=0;
	}
	motor_Speed(left_speed,right_speed);
	straight();
}




void main()
{
 adc_init();
 timer2_init_motor_Speed();
 motor_init();
 
 read_sensor();
 while(1)
 {
	 if(left_sensor<100 && mid_sensor>550 && right_sensor<100)   // only center on black (on straight black line)
	{
		 straight();
	}
	else if(left_sensor>550 && mid_sensor>550 && right_sensor>550)    //all three on black(node reached)
	{
		right();
	}
	else if(left_sensor>550 && mid_sensor<100 && right_sensor<100)    //only left on black  
	{
		left_correction();
	}
	else if(left_sensor<100 && mid_sensor<100 && right_sensor>550)    //only right on black
	{
		right_correction();
	}
	else if(left_sensor>550 && mid_sensor>550 && right_sensor<100)     //left and centre on black(misalignment)
	{
		left_correction();
	}
	else if(left_sensor<100 && mid_sensor>550 && right_sensor>550)     //right and centre on black(misalignment)
	{
		right_correction();
	}
}
}

}

