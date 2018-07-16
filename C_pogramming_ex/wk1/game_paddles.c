//displays a pair of game paddles

#include "cab202_graphics.h"
void draw_paddles( void ) {
	// INSERT CODE HERE
	int h = screen_height();
	int lt = ((h-9)/2) + 2;
	int lb = lt + 8;
	int rt =((h-9)/2) - 4;
	int rb = rt +8;
	int x = screen_width()-4;
	draw_line(3,lt,3,lb,'$');
	draw_line(x,rt,x,rb,'$');
	show_screen( );
}
int main( void ) {
	setup_screen();
	draw_paddles();
	draw_string( 0, screen_height( ) - 1, "Press any key to finish..." );
	wait_char();
	cleanup_screen();
	return 0;
}