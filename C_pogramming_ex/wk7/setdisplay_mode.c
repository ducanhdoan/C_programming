// Implement a Teensy program that allows the user to set the display mode of the LCD display.

#include <avr/io.h>
#include <util/delay.h>
#include <cpu_speed.h>
#include <graphics.h>
#include <lcd.h>
#include <macros.h>
#include "lcd_model.h"

void setup( void ) {
	set_clock_speed(CPU_8MHz);

	//	(a) Enable input from the Left, Right, Up, and Down switches
	//	of the joystick.
	SET_BIT(DDRB,1);
	SET_BIT(DDRD,0);
	SET_BIT(DDRD,1);
	SET_BIT(DDRB,7);

	//	(b) Initialise the LCD display using the default contrast setting.
	lcd_init(LCD_DEFAULT_CONTRAST);

	//	(c) Use one of the functions declared in "graphics.h" to display 
	//	your student number, "n9812482", using the foreground colour, 
	//	positioning the left edge of the text at 19 and the nominal top 
	//	of the text at 15.
	char *hello="n9812482";
	draw_string(19,15,hello,FG_COLOUR);

	//	(d) Use one of the functions declared in "graphics.h" to copy 
	//	the contents of the screen buffer to the LCD.
	show_screen();
}

void process( void ) {
	//  (e) Determine if the Up joystick switch is closed. 
	//	If it is, set the LCD display to enter normal video mode.

	// lcd_write(LCD_C, 0b00001001); // everything on

	if (BIT_IS_SET(PIND,1))
	{
		/* code */
		lcd_write(LCD_C, 0b00001100); // normal mode
	}


	//  (f) OTHERWISE, determine if the Down joystick switch 
	//	is closed. If it is, set the LCD display to switch to inverse video mode.
	else if (BIT_IS_SET(PINB,7))
	{
		/* code */
		lcd_write(LCD_C, 0b00001101);// inverse mode
	}

	//  (g) OTHERWISE, determine if the Left joystick switch 
	//	is closed. If it is, set the LCD display to turn off all pixels.
	else if (BIT_IS_SET(PINB,1))
	{
		/* code */
		lcd_write(LCD_C, 0b00001000); // everything blank
	}

	//  (h) OTHERWISE, determine if the Right joystick switch 
	//	is closed. If it is, set the LCD display to turn on all pixels.
	else if (BIT_IS_SET(PIND,0))
	{
		/* code */
		lcd_write(LCD_C, 0b00001001); // everything on
	}


	//	If none of the joystick switches are closed, do nothing.
	//	(Hint: do not insert any more instructions.)
}


int main(void) {
	setup();

	for ( ;; ) {
		process();
		_delay_ms(100);
	}

	return 0;
}
