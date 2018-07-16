// displays several bubbles on the screen.

#include "cab202_graphics.h"

void draw_bubbles(void){
	// (a) Draw a bubble at (63,20)
	draw_char(63,20,'O');

	// (b) Draw a bubble at (22,21)
	draw_char(22,21,'O');
	// (c) Draw a bubble at (38,15)
	draw_char(38,15,'O');
	// (d) Draw a bubble at (13,6)
	draw_char(13,6,'O');
	// Keep the following line without change.
	show_screen();
}

int main( void ) {
	setup_screen();

	draw_bubbles();

	draw_string( 0, screen_height() - 1, "Press any key to finish..." );
	wait_char();
	cleanup_screen();
	return 0;
}