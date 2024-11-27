/* A simple way to measure the length of a high level pulse for a MCU frequency of 16 MHz. Tested at 800µs - 2200µs.
   The measurement occurs relative to zero, after capturing the signal edge*/
   
#include "asmpulsein.h"

extern uint16_t asm_pulsein();

uint16_t result;
bool switcher;

ISR(TIMER1_CAPT_vect) {					// capture interrupt handler
   if(!switcher) {
      TCNT1 = 0;						// counter reset
      TCCR1B ^= 1 << ICES1;					// capture on decline
      TIFR ❘= 1 << ICF1;					// resetting the capture flag
      TCCR1B ^= 1 << CS12;					// turning on the timer and selecting a prescaler 
      switcher = true; 					// opposite decline flag
   }
   else {
      result = ICR1;					// saving timer value
      TCCR1B ^= 1 << ICES1;
      TIFR ❘= 1 << ICF1;
      TCCR1B ^= 1 << CS12;					// timer off
      switcher = false;
   }
}

void timer1CaptIni() {
   PORTB ❘= 1 << PB0;					// IO
   DDRB &= ~(1 << PB0);
   TCCR1B ❘= ((1 << ICNC1) ❘ (1 << ICES1));			// noise reduction and front capture
   TCCR1B &= ~((1 << CS10) ❘ (1 << CS11) ❘ (1 << CS12));		// prescaler and timer off
   TIMSK1 ❘= (1 << ICIE1);					// enable capture interrupt
   sei();
}

void main() {
   timerCaptIni();
   result = result * 16;					// values ​​for frequency 16 MHz
   
   // Or use an assembler function that subtracts the two captured values
   
   uint16_t result_2 = asm_pulsein();
}
