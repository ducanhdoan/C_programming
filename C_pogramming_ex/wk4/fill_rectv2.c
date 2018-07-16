//filling in rect boxes

#include <stdlib.h>
#include <cab202_graphics.h>

//  (a) Begin the definition a function called fill_rect that returns nothing, 
//      but requires the following arguments:
//      l - an integer that specifies the absolute horizontal location 
//          of the left hand side of the rectangle.
//      t - an integer that specifies the absolute vertical location 
//          of the upper edge of the rectangle.
//      r - an integer that specifies the absolute horizontal location 
//          of the right hand side of the rectangle.
//      b - an integer that specifies the absolute vertical location 
//          of the lower edge of the rectangle.
//      symbol = a character value that will be used to draw the
//          display the rectangle.

    //  (c) Test to see if either the width or height of the rectangle is less 
    //      than 1. If so, the function should stop immediately and draw nothing.

    //  (d) Use statements of your own choice to fill the region defined by the
    //      first four arguments with the designated character value. 

//  (b) End the definition of fill_rect.
void fill_rect(int l,int t,int r,int b,char symbol){
    if (r-l<1 || b-t<1)
    {
        /* code */
        if (r-l==0)
        {
            /* code */
            draw_line(l,t,l,b,symbol);
        }
        if (b-t==0)
        {
            /* code */
            draw_line(l,t,r,t,symbol);
        }
        return;
    }
    for (int y_ctr = t; y_ctr < b+1; y_ctr++)
    {
        /* code */
        draw_line(l,y_ctr,r,y_ctr,symbol);
    }
}

void hrule( void );
void vrule( void );

int main( void ) {
    setup_screen();

    // draw a box.
    int l = 2 + rand() % ( screen_width() - 2 ) / 2;
    int t = 2 + rand() % ( screen_height() - 2 ) / 2;
    int r = l + 1 + rand() % ( screen_width() - l - 1 );
    int b = t + 1 + rand() % ( screen_height() - t - 1 );
    int symbol = '@';
    clear_screen();
    hrule();
    vrule();
    draw_formatted( 5, 1,
        "left: %4d, upper: %4d, right: %4d, lower: %4d - Press key to continue...",
        l, t, r, b
        );
    fill_rect( l, t, r, b, symbol );
    show_screen();
    wait_char();

    // draw a box.
    l = 2 + rand() % ( screen_width() - 2 ) / 2;
    t = 2 + rand() % ( screen_height() - 2 ) / 2;
    r = l + 1 + rand() % ( screen_width() - l - 1 );
    b = t + 1 + rand() % ( screen_height() - t - 1 );
    symbol = '&';
    clear_screen();
    hrule();
    vrule();
    draw_formatted( 5, 1,
        "left: %4d, upper: %4d, right: %4d, lower: %4d - Press key to continue...",
        l, t, r, b
        );
    fill_rect( l, t, r, b, symbol );
    show_screen();
    wait_char();

    // draw a box with zero width.
    l = 2 + rand() % ( screen_width() - 2 ) / 2;
    t = 2 + rand() % ( screen_height() - 2 ) / 2;
    r = l - 1;
    b = t + 1 + rand() % ( screen_height() - t - 1 );
    symbol = '*';
    clear_screen();
    hrule();
    vrule();
    draw_formatted( 5, 1,
        "left: %4d, upper: %4d, right: %4d, lower: %4d - Press key to continue...",
        l, t, r, b
        );
    fill_rect( l, t, r, b, symbol );
    show_screen();
    wait_char();

    // draw a box.
    l = 2 + rand() % ( screen_width() - 2 ) / 2;
    t = 2 + rand() % ( screen_height() - 2 ) / 2;
    r = l + 1 + rand() % ( screen_width() - l - 1 );
    b = t + 1 + rand() % ( screen_height() - t - 1 );
    symbol = '#';
    clear_screen();
    hrule();
    vrule();
    draw_formatted( 5, 1,
        "left: %4d, upper: %4d, right: %4d, lower: %4d - Press key to continue...",
        l, t, r, b
        );
    fill_rect( l, t, r, b, symbol );
    show_screen();
    wait_char();

    // draw a box with negative width.
    l = 2 + rand() % ( screen_width() - 2 ) / 2;
    t = 2 + rand() % ( screen_height() - 2 ) / 2;
    r = l - 2;
    b = t + 1 + rand() % ( screen_height() - t - 1 );
    symbol = '!';
    clear_screen();
    hrule();
    vrule();
    draw_formatted( 5, 1,
        "left: %4d, upper: %4d, right: %4d, lower: %4d - Press key to continue...",
        l, t, r, b
        );
    fill_rect( l, t, r, b, symbol );
    show_screen();
    wait_char();

    // draw a box.
    l = 2 + rand() % ( screen_width() - 2 ) / 2;
    t = 2 + rand() % ( screen_height() - 2 ) / 2;
    r = l + 1 + rand() % ( screen_width() - l - 1 );
    b = t + 1 + rand() % ( screen_height() - t - 1 );
    symbol = '+';
    clear_screen();
    hrule();
    vrule();
    draw_formatted( 5, 1,
        "left: %4d, upper: %4d, right: %4d, lower: %4d - Press key to continue...",
        l, t, r, b
        );
    fill_rect( l, t, r, b, symbol );
    show_screen();
    wait_char();

    // draw a box with zero height.
    l = 2 + rand() % ( screen_width() - 2 ) / 2;
    t = 2 + rand() % ( screen_height() - 2 ) / 2;
    r = l + 1 + rand() % ( screen_width() - l - 1 );
    b = t - 1;
    symbol = 'a';
    clear_screen();
    hrule();
    vrule();
    draw_formatted( 5, 1,
        "left: %4d, upper: %4d, right: %4d, lower: %4d - Press key to continue...",
        l, t, r, b
        );
    fill_rect( l, t, r, b, symbol );
    show_screen();
    wait_char();

    // draw a box.
    l = 2 + rand() % ( screen_width() - 2 ) / 2;
    t = 2 + rand() % ( screen_height() - 2 ) / 2;
    r = l + 1 + rand() % ( screen_width() - l - 1 );
    b = t + 1 + rand() % ( screen_height() - t - 1 );
    symbol = 'b';
    clear_screen();
    hrule();
    vrule();
    draw_formatted( 5, 1,
        "left: %4d, upper: %4d, right: %4d, lower: %4d - Press key to continue...",
        l, t, r, b
        );
    fill_rect( l, t, r, b, symbol );
    show_screen();
    wait_char();

    // draw a box with negative right.
    l = 2 + rand() % ( screen_width() - 2 ) / 2;
    t = 2 + rand() % ( screen_height() - 2 ) / 2;
    r = l + 1 + rand() % ( screen_width() - l - 1 );
    b = t - 2;
    symbol = 'c';
    clear_screen();
    hrule();
    vrule();
    draw_formatted( 5, 1,
        "left: %4d, upper: %4d, right: %4d, lower: %4d - Press key to continue...",
        l, t, r, b
        );
    fill_rect( l, t, r, b, symbol );
    show_screen();
    wait_char();

    // draw a box.
    l = 2 + rand() % ( screen_width() - 2 ) / 2;
    t = 2 + rand() % ( screen_height() - 2 ) / 2;
    r = l + 1 + rand() % ( screen_width() - l - 1 );
    b = t + 1 + rand() % ( screen_height() - t - 1 );
    symbol = 'd';
    clear_screen();
    hrule();
    vrule();
    draw_formatted( 5, 1,
        "left: %4d, upper: %4d, right: %4d, lower: %4d - Press key to continue...",
        l, t, r, b
        );
    fill_rect( l, t, r, b, symbol );
    show_screen();
    wait_char();

    cleanup_screen();
    return 0;
}

void hrule( void ) {
    for ( int x = 0; x < screen_width(); x++ ) {
        draw_char( x, 0, '0' + ( x % 10 ) );
    }
}

void vrule( void ) {
    for ( int y = 0; y < screen_height(); y++ ) {
        draw_char( 0, y, '0' + ( y % 10 ) );
    }
}
