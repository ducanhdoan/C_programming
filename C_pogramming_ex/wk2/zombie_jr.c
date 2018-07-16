//moving sprites

#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <cab202_graphics.h>
#include <cab202_sprites.h>
#include <cab202_timers.h>

// Configuration
#define DELAY (10) /* Millisecond delay between game updates */

#define ZOMBIE_WIDTH (5)
#define ZOMBIE_HEIGHT (5)

// Game state.
bool game_over = false; /* Set this to true when game is over */
bool update_screen = true; /* Set to false to prevent screen update. */

char * zombie_image =
/**/	"ZZZZZ"
/**/	"   Z "
/**/	"  Z  "
/**/	" Z   "
/**/	"ZZZZZ";

//	(a) Declare a sprite_id called zombie
sprite_id zombie;

// Setup game.
void setup(void) {
    //  (b) Assign a value to zombie by creating a sprite at integer 
    //      coordinates (x,y). Use integer arithmetic to calculate 
    //      the location relative to the screen dimensions:
    //      x = 80% of available horizontal space on the screen.
    //      y = 80% of available vertical space on the screen.
    //      Use the formula set out in the statement of the problem.
    int w=screen_width();
    int h=screen_height();
    zombie =sprite_create((w-5)*80/100,(h-5)*80/100,ZOMBIE_WIDTH,ZOMBIE_HEIGHT,zombie_image);

    //	(c) Draw the zombie.
    sprite_draw(zombie);
}

// Play one turn of game.
void process(void) {
    //	(d) Get a character code from standard input without waiting.
    int key=get_char();

    //  (e) Get the current screen coordinates of the zombie in integer variables 
    //      by rounding the actual coordinates. Store the coordinates in a pair of
    //      variables called x and y, both of type int.
    int x= sprite_x(zombie);
    int y=sprite_y(zombie);

    //	(f) Move zombie left, ensuring that it always remains within the screen.
    if(key == '4'){
        if (x>1)
        {
            /* code */
            sprite_move(zombie,-1,0);
        }
    }

    //	(g) Move zombie right, ensuring that it always remains within the screen.
    if (key == '6')
    {
        if (x<screen_width()-1-sprite_width(zombie))
        {
            /* code */
            sprite_move(zombie,+1,0);
        }
    }

    //	(h) Move zombie up, ensuring that it always remains within the screen.
    if (key == '8')
    {
        /* code */
        if (y>1)
        {
            /* code */
            sprite_move(zombie,0,-1);
        }
    }

    //	(i) Move zombie down according to specification.
    if (key == '2')
    {
        /* code */
        if (y<screen_height()-1-sprite_height(zombie))
        {
            /* code */
            sprite_move(zombie,0,+1);
        }
    }

    //	(j) If the key is 'q', set game_over to true.
    if (key=='q')
    {
        /* code */
        game_over=true;
    }

    // Leave next line intact.
    clear_screen();

    //	(k)	Draw the zombie.
    sprite_draw(zombie);
}

// Program entry point.
int main(void) {
	setup_screen();
	setup();
	show_screen();

    // while(true);

	while ( !game_over ) {
		process();

		if ( update_screen ) {
			show_screen();
		}

		timer_pause(DELAY);
	}

	return 0;
}