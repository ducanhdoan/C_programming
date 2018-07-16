//fill rect boxes

#include <stdlib.h>
#include <cab202_timers.h>
#include <cab202_graphics.h>

//  (a) Declare four global integer variables, as follows:
//      x - the horizontal location of the left edge of the rectangle
//      y - the vertical location of the top edge of the rectangle 
//      w - the width of the rectangle.
//      h - the height of the rectangle.
int x;
int y;
int w;
int h;

//	(b) Declare a global variable of type char called c.
//      This is the character that is to be used to render the outline of the
//      rectangle.
char c;

void fill_rect(void) {
    //  (c) Test to see if either of w or h is less than 1.
    //      If so, the function should stop immediately and draw nothing.
    if (w<1 || h<1)
    {
        /* code */
        return;
    }
    //  (d) Calculate the x-coordinate of the right-hand side of the rectangle.
    //      Store the value in an integer variable called rect_right.
    int rect_right= x+w-1;
    //  (e) Calculate the y coordinate of the bottom edge of the rectangle.
    //      Store the result in an integer variable called rect_base.
    int rect_base=y+h-1;
    //  (f.a) Set up for loop that uses an integer variable called y_ctr to 
    //      iterate from the top of the rectangle to the bottom of the rectangle.
    //      Initially y_ctr should be equal to y.
    //      The loop body should run while y_ctr is less than or equal to rect_base.
    for (int y_ctr = y; y_ctr <= rect_base; y_ctr++)
    {
        /* code */
        draw_line(x,y_ctr,rect_right,y_ctr,c);
    }
        //  (g) Draw a horizontal line from x to rect_right, with 
        //      y-coordinate equal to y_ctr, using the character specified by 
        //      c.

    //  (f.b) End the loop.
}

int main(void) {
    setup_screen();

    // draw a box.
    x = 1 + rand() % (screen_width() - 1) / 2;
    y = 1 + rand() % (screen_height() - 1) / 2;
    w = 1 + rand() % (screen_width() - x - 1);
    h = 1 + rand() % (screen_height() - y - 1);
    c = '@';
    clear_screen();
    draw_formatted(0, 0,
        "left: %4d, top: %4d, width: %4d, height: %4d - Press key to continue...",
        x, y, w, h
        );
    fill_rect();
    show_screen();
    wait_char();

    // draw a box.
    x = 1 + rand() % (screen_width() - 1) / 2;
    y = 1 + rand() % (screen_height() - 1) / 2;
    w = 1 + rand() % (screen_width() - x - 1);
    h = 1 + rand() % (screen_height() - y - 1);
    c = '&';
    clear_screen();
    draw_formatted(0, 0,
        "left: %4d, top: %4d, width: %4d, height: %4d - Press key to continue...",
        x, y, w, h
        );
    fill_rect();
    show_screen();
    wait_char();

    // draw a box with zero width.
    x = 1 + rand() % (screen_width() - 1) / 2;
    y = 1 + rand() % (screen_height() - 1) / 2;
    w = 0;
    h = 1 + rand() % (screen_height() - y - 1);
    c = '*';
    clear_screen();
    draw_formatted(0, 0,
        "left: %4d, top: %4d, width: %4d, height: %4d - Press key to continue...",
        x, y, w, h
        );
    fill_rect();
    show_screen();
    wait_char();

    // draw a box.
    x = 1 + rand() % (screen_width() - 1) / 2;
    y = 1 + rand() % (screen_height() - 1) / 2;
    w = 1 + rand() % (screen_width() - x - 1);
    h = 1 + rand() % (screen_height() - y - 1);
    c = '#';
    clear_screen();
    draw_formatted(0, 0,
        "left: %4d, top: %4d, width: %4d, height: %4d - Press key to continue...",
        x, y, w, h
        );
    fill_rect();
    show_screen();
    wait_char();

    // draw a box with negative width.
    x = 1 + rand() % (screen_width() - 1) / 2;
    y = 1 + rand() % (screen_height() - 1) / 2;
    w = -rand() % screen_width();
    h = 1 + rand() % (screen_height() - y - 1);
    c = '!';
    clear_screen();
    draw_formatted(0, 0,
        "left: %4d, top: %4d, width: %4d, height: %4d - Press key to continue...",
        x, y, w, h
        );
    fill_rect();
    show_screen();
    wait_char();

    // draw a box.
    x = 1 + rand() % (screen_width() - 1) / 2;
    y = 1 + rand() % (screen_height() - 1) / 2;
    w = 1 + rand() % (screen_width() - x - 1);
    h = 1 + rand() % (screen_height() - y - 1);
    c = '+';
    clear_screen();
    draw_formatted(0, 0,
        "left: %4d, top: %4d, width: %4d, height: %4d - Press key to continue...",
        x, y, w, h
        );
    fill_rect();
    show_screen();
    wait_char();

    // draw a box with zero height.
    x = 1 + rand() % (screen_width() - 1) / 2;
    y = 1 + rand() % (screen_height() - 1) / 2;
    w = 1 + rand() % (screen_width() - x - 1);
    h = 0;
    c = 'a';
    clear_screen();
    draw_formatted(0, 0,
        "left: %4d, top: %4d, width: %4d, height: %4d - Press key to continue...",
        x, y, w, h
        );
    fill_rect();
    show_screen();
    wait_char();

    // draw a box.
    x = 1 + rand() % (screen_width() - 1) / 2;
    y = 1 + rand() % (screen_height() - 1) / 2;
    w = 1 + rand() % (screen_width() - x - 1);
    h = 1 + rand() % (screen_height() - y - 1);
    c = 'b';
    clear_screen();
    draw_formatted(0, 0,
        "left: %4d, top: %4d, width: %4d, height: %4d - Press key to continue...",
        x, y, w, h
        );
    fill_rect();
    show_screen();
    wait_char();

    // draw a box with negative width.
    x = 1 + rand() % (screen_width() - 1) / 2;
    y = 1 + rand() % (screen_height() - 1) / 2;
    w = 1 + rand() % (screen_width() - y - 1);
    h = -rand() % screen_height();
    c = 'c';
    clear_screen();
    draw_formatted(0, 0,
        "left: %4d, top: %4d, width: %4d, height: %4d - Press key to continue...",
        x, y, w, h
        );
    fill_rect();
    show_screen();
    wait_char();

    // draw a box.
    x = 1 + rand() % (screen_width() - 1) / 2;
    y = 1 + rand() % (screen_height() - 1) / 2;
    w = 1 + rand() % (screen_width() - x - 1);
    h = 1 + rand() % (screen_height() - y - 1);
    c = 'd';
    clear_screen();
    draw_formatted(0, 0,
        "left: %4d, top: %4d, width: %4d, height: %4d - Press key to continue...",
        x, y, w, h
        );
    fill_rect();
    show_screen();
    wait_char();

    timer_pause(5000);
    cleanup_screen();
    return 0;
}
