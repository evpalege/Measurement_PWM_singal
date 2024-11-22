/*Assembly function measurement PWM for MCU clk = 8 MHz*/

#include "asmpulsein.h"
#include <avr/io.h>

.global asm_pulsein

asm_pulsein:
	ldi r20, 0xC1	// itializing timer capture ICNC = 1, ICES = 1, CS1 = 1
	sts TCCR1B, r20
wait_front:
	ldi r22, 0x20
	lds r23, TIFR1
	and r23, r22
	tst r23
	breq wait_front	// waiting for the flag ICF1
	ldi r21, 0x20
	sts TIFR1, r21	// resetting the flag
	lds r30, ICR1L	// saving the timer's tick counter
	lds r31, ICR1H
	ldi r20, 0x81
	sts TCCR1B, r20
wait_drop:
	ldi r18, 0x20	// itializing for drop
	lds r19, TIFR1
	and r19, r18
	tst r19
	breq wait_drop	// waiting for the flag ICF1
	ldi r20, 0x20
	sts TIFR1, r20	// resetting the flag
	lds r24, ICR1L	// saving the timer's tick counter
	lds r25, ICR1H
	sub r24, r30	// subtract the final value from the first one
	sbc r25, r31	// result of func in r31r30 registers
	
	//lsr r25		// for MCY clk = 16 MHz (division by two)
	//ror r24
	
	ret
