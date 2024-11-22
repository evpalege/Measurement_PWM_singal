1) Include the file -> #include "asmpulsein"
2) Declare a function in the global scope -> extern uint16_t asm_pulsein();
3) The chip uses timer1 in capture mode AVR MCU 8-bit (Atmega328p -> PB0)
4) In the C program, call the function like uint16_t a = asm_pulsein(); // the result is in microseconds depending on the clock frequency 8 or 16 MHz
