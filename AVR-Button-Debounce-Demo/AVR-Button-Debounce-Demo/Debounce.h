#ifndef DEBOUNCE_H_
#define DEBOUNCE_H_

//Includes 
#include <avr/io.h>

//Definitions
#define DEBOUNCE_MAX 10

//Global variables
volatile uint8_t DebounceBuffer[DEBOUNCE_MAX];
uint8_t DebouncePreviousPortState;


//Function declarations 
void DebounceISR();
uint8_t DebounceGet();
#endif 