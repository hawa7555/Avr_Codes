#define PA0_INPUT (DDRA=DDRA &~(1<<0))
#define PA1_INPUT (DDRA=DDRA &~(1<<1))

#define PC0_OUTPUT (DDRC=DDRC|(1<<0))
#define PC1_OUTPUT (DDRC=DDRC|(1<<1))

#define SW0 (PINA&(1<<0))
#define SW1 (PINA&(1<<1))

#define LED0_ON (PORTC=PORTC|(1<<0))
#define LED1_ON (PORTC=PORTC|(1<<1))

#define LED0_OFF (PORTC=PORTC&~(1<<0))
#define LED1_OFF (PORTC=PORTC&~(1<<1))