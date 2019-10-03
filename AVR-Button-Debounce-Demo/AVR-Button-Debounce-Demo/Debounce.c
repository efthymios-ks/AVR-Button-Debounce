#include "Debounce.h"

void DebounceISR()
{
	//Declared as static so it retains its value on each call
	//Initialized only once
	volatile static int8_t debounceCounter = DEBOUNCE_MAX - 1;

	//Get an input sample
	DebounceBuffer[debounceCounter] = PINA;

	//Roll counter
	debounceCounter--;
	if (debounceCounter < 0)
	debounceCounter = DEBOUNCE_MAX - 1;
}

uint8_t DebounceGet()
{
	uint8_t newState;
	uint8_t and = 0xFF;
	uint8_t or = 0x00;

	//Process data
	for (int8_t i = (DEBOUNCE_MAX - 1); i >= 0; i--)
	{
		//Temporarily use newState variable
		newState = DebounceBuffer[i];
		and &= newState;
		or |= newState;
	}

	//Get previous state
	newState = DebouncePreviousPortState;

	//Keep '1' from AND
	newState |= and;
	//Keep '0' from OR
	newState &= or;

	//Bits that changed state (XOR)
	//	A | B | Y
	//	0 | 0 | 0
	//	0 | 1 | 0 <-
	//	1 | 0 | 1 <-
	//	1 | 1 | 0
	//uint8_t changedBits = newState ^ DebouncePreviousPortState;

	//Update previous state
	DebouncePreviousPortState = newState;

	return newState;
}