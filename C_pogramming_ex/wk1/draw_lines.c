//displays several lines on screen

#include "cab202_graphics.h"

void draw_lines(void){
	// (a) Draw a line from (50,7) to (27,7).
	draw_line(50,7,27,7,'@');
	// (b) Draw a line from (27,7) to (39,3).
	draw_line(27,7,39,3,'@');
	// (c) Draw a line from (39,3) to (51,8).
	draw_line(39,3,51,8,'@');
	// (d) Draw a line from (51,8) to (50,7).
	draw_line(51,8,50,7,'@');
	// Leave the following instruction unchanged.
	show_screen();
}

int main( void ) {
	setup_screen( );

	draw_lines();

	draw_string( 0, screen_height( ) - 1, "Press any key to finish..." );
	wait_char( );
	cleanup_screen( );
	return 0;
}