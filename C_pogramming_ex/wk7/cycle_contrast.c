// Implement a Teensy program that allows the user to set the contrast level on the LCD display.

#include <avr/io.h>
#include <util/delay.h>
#include <cpu_speed.h>
#include <macros.h>
#include <graphics.h>
#include <lcd.h>
#include "lcd_model.h"

void setup( void ) {
	set_clock_speed(CPU_8MHz);

	//	(a) Enable input from the joystick-up switch and joystick-down switch.
	SET_BIT(DDRD,1);
	SET_BIT(DDRB,7);

	//	(b) Initialise the LCD display using the default contrast setting.
	lcd_init(LCD_DEFAULT_CONTRAST);
	//	(c) Use one of the functions declared in "graphics.h" to display 
	//	your student number, "n9812482", using the foreground colour, 
	//	positioning the left edge of the text at 13 and the nominal top 
	//	of the text at 15.
	char *hello="n9812482";
	draw_string(13,15,hello,FG_COLOUR);

	//	(d) Use one of the functions declared in "graphics.h" to copy the contents 
	//	of the screen buffer to the LCD.
	show_screen();
}

//	(e) Declare a global variable of type int named contrast and 
//	initialise it to the default LCD contrast.
int contrast=LCD_DEFAULT_CONTRAST;
// uint8_t contrast =0 ;

void process(void) {
	//	(f) Test pin corresponding to joystick-down switch. If closed,
	//	decrement contrast by 9. If the result is less than zero,
	//	set contrast to the maximum permitted LCD contrast value.
	if (BIT_IS_SET(PINB,7))
	{
		/* code */
		contrast-=9;
		if (contrast<0)
		{
			/* code */
			contrast=127;
		}
	}

	//	(g) Test pin corresponding to joystick-up switch. If closed,
	//	increment contrast by 9. If the result is greater
	//	then the maximum permitted LCD contrast value, set contrast 
	//	to zero.
	if (BIT_IS_SET(PIND,1))
	{
		/* code */
		contrast+=9;
		if (contrast>127)
		{
			/* code */
			contrast=0;
		}
	}

	//	(h) Send a sequence of commands to the LCD to enable extended
	//	instructions, set contrast to the current value of contrast, 
	//	and finally retore the LCD to basic instruction mode.
	LCD_CMD(lcd_set_function,lcd_instr_extended);
	LCD_CMD(lcd_set_contrast,contrast);
	LCD_CMD(lcd_set_function,lcd_instr_basic);
}


int main(void) {
	setup();

	for ( ;; ) {
		process();
		_delay_ms(100);
	}

	return 0;
}
