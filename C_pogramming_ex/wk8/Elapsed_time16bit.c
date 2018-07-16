// Implement and test a function called get_current_time which computes the elapsed time from power-up in a Teensy. the program will use a designated 16-bit timer in normal mode, with overflow interrupt handling

#include <stdint.h>
#include <stdio.h>
#include <avr/io.h> 
#include <avr/interrupt.h>
#include <util/delay.h>
#include <cpu_speed.h>

#include <graphics.h>
#include <macros.h>
#include "lcd_model.h"

void draw_double(uint8_t x, uint8_t y, double value, colour_t colour);
void draw_int(uint8_t x, uint8_t y, int value, colour_t colour);

void setup(void) {
	set_clock_speed(CPU_8MHz);
	lcd_init(LCD_DEFAULT_CONTRAST);
	lcd_clear();

	//	(a) Initialise Timer 1 in normal mode so that it overflows 
	//	with a period of approximately 2.1 seconds.
	//	Hint: use the table you completed in a previous exercise.
	TCCR1A=0;
	TCCR1B=4;


	//	(b) Enable timer overflow for Timer 1.
	TIMSK1=1;

	//	(c) Turn on interrupts.
	sei();

	//	(d) Display your student number, "n9812482", with nominal top-left
	//	corner at screen location (30,22). Left-aligned 10
	//	pixels below that, display the pre-scale factor that corresponds
	//	to a timer overflow period of approximately 2.1 
	//	seconds.
	char *hello="n9812482";
	draw_string(30,22,hello,FG_COLOUR);
	draw_int(30,32,256,FG_COLOUR);

	// Keep the next instruction intact.
	show_screen();
}

//	(e) Create a volatile global variable called counter.
//	The variable should be a 32-bit unsigned integer of type uint32_t. 
//	Initialise the variable to 0.
volatile uint32_t counter=0;

//	(f) Define an interrupt service routine to process timer overflow
//	interrupts for Timer 1. Every time the interrupt service
//	routine is called, counter should increment by 1.
ISR(TIMER1_OVF_vect) {
	counter ++;
}


//	(g) Define a function called get_current_time which has
//	no parameters, but returns a value of type double which contains
//	the total elapsed time measured up to the time at which it is called.
//	Use the method demonstrated in the Topic 9 lecture to compute the
//	elapsed time, taking into account the fact that the timer counter has 
//	16 bits rather than 8 bits.
double get_current_time(){
	double time = ( counter * 65536.0 + TCNT1 ) * 256.0  / 8000000.0;
	return time;
}

// -------------------------------------------------
// Helper functions.
// -------------------------------------------------

char buffer[20];

void draw_double(uint8_t x, uint8_t y, double value, colour_t colour) {
	snprintf(buffer, sizeof(buffer), "%f", value);
	draw_string(x, y, buffer, colour);
}

void draw_int(uint8_t x, uint8_t y, int value, colour_t colour) {
	snprintf(buffer, sizeof(buffer), "%d", value);
	draw_string(x, y, buffer, colour);
}


// -------------------------------------------------
// Test driver.
// -------------------------------------------------

void process(void) {
	double time = get_current_time();
	draw_string(0, 0, "Time = ", FG_COLOUR);
	draw_string(10, 10, "           ", FG_COLOUR);
	draw_double(10, 10, time, FG_COLOUR);
	show_screen();
}

int main(void) {
	setup();

	for ( ;; ) {
		process();
	}
}
