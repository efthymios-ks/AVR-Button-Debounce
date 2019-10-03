#include <avr/io.h>
#include <avr/interrupt.h>
#include "Debounce.h"

//Function declarations
inline void SetupIO();
inline void SetupTimer0_1ms();
ISR(TIMER0_COMP_vect);

int main()
{
	SetupTimer0_1ms();
	SetupIO();
	sei();

	while (1)
	{
		uint8_t portSafeA = DebounceGet();

		//If button set
		if (portSafeA & (1<<0))
		{
			//Set LED
			PORTA |= (1<<1);
		}
		else
		{
			//Reset LED
			PORTA &= ~(1<<1);
		}

	}

	return 0;
}

//Function definitions
inline void SetupIO()
{
	//PA.0 = Input (Active High) = Button
	DDRA &= (1<<0);
	PORTA &= (1<<0);

	//PA.1 = Output = LED
	DDRA |= (1<<1);
}

inline void SetupTimer0_1ms()
{
	//CTC mode
	//	WGM01 = 1
	//	WGM00 = 0
	TCCR0 &= ~(1<<WGM00);
	TCCR0 |= (1<<WGM01);

	//1ms
	//	CPU				= 8HMz
	//	Prescaler		= 64
	//	Timer ticks		= 125
	//	OCR				= Timer ticks - 1
	//					= 125 - 1 = 124
	OCR0 = 124;

	//Prescaler	= 64
	//	CTC02	= 0
	//	CTC01	= 1
	//	CTC00	= 0
	TCCR0 &= ~(1<<CS02);
	TCCR0 |= ((1<<CS01) | (1<<CS00));

	//Enable CTC interrupt
	TIMSK |= (1<<OCIE0);
}


ISR(TIMER0_COMP_vect)
{
	DebounceISR();
}