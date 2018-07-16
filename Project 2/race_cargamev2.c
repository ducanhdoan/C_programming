//race_car game in teensy pew pew hardware.

#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <stdbool.h>

#include <avr/io.h> 
#include <avr/interrupt.h>
#include <util/delay.h>
#include <cpu_speed.h>

#include <graphics.h>
#include <sprite.h>
#include <macros.h>
#include "lcd_model.h"
#include <ascii_font.h>
#include "usb_serial.h"
#include "cab202_adc.h"


Sprite car;
Sprite house[5];
Sprite obstacles[3];
int obstacles_count=2;
Sprite fuelstation;
Sprite tree[5];
int offroad_count=4;
Sprite finish;


double speed =0;
char buffer[80];
char buff[80];
int HP=100;
int fuel=500;
int distance=0;
double pausetime=0;
bool ispaused=false;
bool offscreen=false;	
int change_inpos=0;	
bool cross_finish_line=false;
// uint8_t lcd_contrast=0;
bool new_game=true;
bool game_over=false;
//setting an interrupt for 16bit timer
volatile uint32_t counter=0;

volatile uint8_t left_button=0;
volatile uint8_t pressed=0;

volatile uint8_t right_button=0;
volatile uint8_t right_pressed=0;

volatile uint8_t L_JOYSTICK=0;
volatile uint8_t left_joy_state=0;

volatile uint8_t R_Joystick=0;
volatile uint8_t right_joy_state=0;

volatile uint8_t U_joystick=0;
volatile uint8_t up_joy_state=0;

volatile uint8_t D_joystick=0;
volatile uint8_t down_joy_state=0;

volatile uint8_t C_joystick=0;
volatile uint8_t centre_joy_state=0;

#define BIT(x) (1 << (x))


void draw_int(uint8_t x, uint8_t y, int value, colour_t colour);
double get_current_time(void);
bool car_near_fuel(void);
void draw_char_direct(int x, int y, char ch, colour_t colour);
void draw_string_direct(int x, int y, char * str, colour_t colour);
//8,9
uint8_t car_img[]={
	0b00011000,
	0b10100101,
	0b01000010,
	0b01000010,
	0b11111111,
	0b01000010,
	0b01000010,
	0b10100101,
	0b00011000,

};
// 8,7
uint8_t tree_img[]={
	0b00011000,
	0b01111110,
	0b11111111,
	0b11111111,
	0b00111100,
	0b00011000,
	0b00011000,


};
//8,8
uint8_t house_img[]={
	0b11111111,
	0b11111111,
	0b10111011,
	0b11111111,
	0b11111111,
	0b10011111,
	0b10011111,
	0b10011111,

};

//8,11
uint8_t fuelstation_img[]={
	0b11111111,
	0b10000001,
	0b10000001,
	0b11111111,
	0b11111101,
	0b11111111,
	0b10010101,
	0b10011111,
	0b10011111,
	0b11111111,
	0b11111111,
};

//8,4
uint8_t obstacles_img[]={
	0b00011000,
	0b00011000,
	0b00111100,
	0b01111110,

};

//32,4
uint8_t finish_lineimg[]={
	0b11111111,0b11111111,0b11111111,0b11111000,
	0b10011000,0b00011000,0b00011000,0b01100000,
	0b10011000,0b00011000,0b00011000,0b01100000,
	0b11111111,0b11111111,0b11111111,0b11111000,
};

//change the position of string
void welcome(void){
	lcd_clear();
	clear_screen();
	
	draw_string_direct((LCD_X - 6 * CHAR_WIDTH) / 2 - 20, (1 * CHAR_HEIGHT)-3, "RACING CAR GAME", FG_COLOUR);
	draw_string_direct((LCD_X - 6 * CHAR_WIDTH) / 2 - 23, (2 * CHAR_HEIGHT)-3, "KEVIN GUNAWAN", FG_COLOUR);
	draw_string_direct((LCD_X - 6 * CHAR_WIDTH) / 2 - 23, (3 * CHAR_HEIGHT)-3, "n9812482", FG_COLOUR);
	draw_string_direct((LCD_X - 6 * CHAR_WIDTH) / 2-22, 4 * CHAR_HEIGHT, "L-BTN OR R-BTN ", FG_COLOUR);
	draw_string_direct((LCD_X - 6 * CHAR_WIDTH) / 2-10, 5 * CHAR_HEIGHT, "TO CONTINUE ", FG_COLOUR);
 	while(!right_pressed && !pressed){

 	}
 	lcd_clear();
 	
 	while(right_pressed){

 	}
 	offscreen=true;
}

void draw_char_direct(int x, int y, char ch, colour_t colour) {
    // Do nothing if character does not fit on LCD.
    if (x < 0 || x > LCD_X - CHAR_WIDTH || y < 0 || y > LCD_Y - CHAR_HEIGHT) {
        return;
    }

    // Move LCD cursor to starting spot.
    LCD_CMD(lcd_set_function, lcd_instr_basic | lcd_addr_horizontal);
    LCD_CMD(lcd_set_x_addr, (x & 0x7f));
    LCD_CMD(lcd_set_y_addr, (y & 0x7f) / 8);

    // Send pixel blocks.
    for (int i = 0; i < CHAR_WIDTH; i++) {
        uint8_t pixelBlock = pgm_read_byte(&(ASCII[ch - ' '][i]));

        if (colour == BG_COLOUR) {
            pixelBlock = ~pixelBlock;
        }

        LCD_DATA(pixelBlock);
    }
}

void draw_string_direct(int x, int y, char * str, colour_t colour) {
    for (int i = 0; str[i] != 0; i++, x += CHAR_WIDTH) {
        draw_char_direct(x, y, str[i], colour);
    }
}

void setup_car(void){
	int x= LCD_X/2;
	int y= LCD_Y-9;
	sprite_init(&car, x, y, 8, 9,car_img) ;
}

void setup_tree(void){
	int road_left=(LCD_X/6)*2;
	for (int i = 0; i < offroad_count; i++)
	{
		int x= rand() % (road_left-17);
		int y= rand() % (LCD_Y);
		sprite_init(&tree[i],x,y,8,7,tree_img);
	}	
}

void setup_house(void){
	int road_right=(LCD_X/6)*4;
	for (int i = 0; i < offroad_count; i++)
	{
		/* code */
		int x= road_right+9+(rand()%(LCD_X-17-road_right));
		int y= rand() %(LCD_Y);
		sprite_init(&house[i],x,y,8,8,house_img);
	}
	
}

void setup_depot(void){
	int left_pos=(LCD_X/6)*2-8;
	int right_pos=(LCD_X/6)*4+1;
	// int y= rand()%(LCD_Y);
	int y=-5;
	int random[2]={left_pos,right_pos};
	int initial=rand()%2;
	int pos_x=random[initial];
	sprite_init(&fuelstation,pos_x,y,8,11,fuelstation_img);
}

void setup_obstacles(void){
	int road_left=(LCD_X/6)*2;
	int road_right=(LCD_X/6)*4-8;
	for (int i = 0; i < obstacles_count; i++)
	{
		/* code */
		int y= rand() %(LCD_Y-11);
		int x= road_left+1+(rand()%(road_right-road_left));
		sprite_init(&obstacles[i],x,y,8,4,obstacles_img);
	}
	

}

void step_tree(sprite_id tree){
	int h=LCD_Y;
	int road_left=(LCD_X/6)*2;

	double dy= speed*0.5;
	tree->y+=dy;

	if (tree->y >= h)
	{
		int pos_x= rand() % (road_left-17);
		int offset= pos_x- tree->x;
		tree->y-=(h+7-3);
		tree->x+=offset;
	}

}

void step_house(sprite_id house){
	int h=LCD_Y;
	int road_right=(LCD_X/6)*4;
	double dy= speed*0.5;
	house->y+=dy;
	if (house->y >= h)
	{
		/* code */
		int pos_x= road_right+9+(rand()%(LCD_X-17-road_right));
		int offset=pos_x - house->x;
		house->y -=(h+8-3);
		house->x +=offset;
	}
}

void step_fuelstation(sprite_id fuelstation){
	int h=LCD_Y;
	int left_pos=(LCD_X/6)*2-8;
	int right_pos=(LCD_X/6)*4+1;
	int random[2]={left_pos,right_pos};
	int position=random[change_inpos];
	if ((fuel>=300 && fuel<=400) || (fuel<=100))
	{
		/* code */
		double dy= speed*0.5;
		fuelstation->y+=dy;
		

		if (fuelstation->y >=h)
		{
			/* code */
			fuelstation->y -=(h+11-3);
			fuelstation->x = position;
			change_inpos+=1;
			change_inpos %=2;
		}
	}
	else if (((fuel>=400)|| (fuel<=300 &&fuel>=100)) && car_near_fuel())
	{
		/* code */
		if (speed>0)
		{
			/* code */
			fuelstation->y =-5;
		}
	}
	else{
		fuelstation->y =-5;
	}

}
//checking whether car is beside fuelstation
bool car_near_fuel(void){
	int left_car=round(car.x);
	int right_car=left_car+8;
	int top_car=round(car.y);
	int bottom_car=top_car+9;

	int left_fuelstation=round(fuelstation.x);
	int right_fuelstation=left_fuelstation+8;
	int top_fuelstation=round(fuelstation.y);
	int bottom_fuelstation=top_fuelstation+11;

	if (top_car<top_fuelstation)
	{
		/* code */
		return false;
	}
	if (bottom_car>bottom_fuelstation)
	{
		/* code */
		return false;
	}
	if (left_car>right_fuelstation+2)
	{
		/* code */
		return false;
	}
	if (right_car<left_fuelstation-2)
	{
		/* code */
		return false;
	}

	return true;
}
//refilling
void refill(void){
	static double last_moved=0;
	static double arrival_time=0;
	int old_fuel=0;

	if (speed>0)
	{
		/* code */
		last_moved=get_current_time();
	}
	else if(car_near_fuel()){
		if (arrival_time<last_moved)
		{
			/* code */
			arrival_time=get_current_time();
			old_fuel=fuel;
		}
		else{
			double time_parked=get_current_time()-arrival_time;
			if (time_parked>=3.0)
			{
				/* code */
				fuel=500;
			}
			else{
				//y=166.67x, y=fuel,x=time
				//either fuel++ or below.
				fuel+=(500-old_fuel/3)/100;
				if (fuel>=500)
				{
					/* code */
					fuel=500;
				}
				// fuel+=time_parked;
			}
		}
	}
}

void step_obstacles(sprite_id obstacles){
	int h=LCD_Y;
	int road_left=(LCD_X/6)*2;
	int road_right=(LCD_X/6)*4-8;

	double dy= speed*0.5;
	obstacles->y+=dy;
	if (obstacles->y >= h)
	{
		/* code */
		int pos_x= road_left+1+(rand()%(road_right-road_left));
		int offset= pos_x- obstacles->x;
		obstacles->y -=(h+8-3);
		obstacles->x +=offset;
	}
}

void setup_finishline(void){
	int road_left=(LCD_X/6)*2;
	int y= 1;
	sprite_init(&finish,road_left,y,32,4,finish_lineimg);
}
//Change the distance and use the cross_finish_line for gameover dialogue!!!
void step_finishline(sprite_id finish){
	if (distance>=2000 && speed>0)
	{
		/* code */
		double dy= speed*0.5;
		finish->y+=dy;
	}
	if (car.y<= finish->y)
	{
		/* code */
		cross_finish_line=true;
	}
}


void dashboard(void){
	int left=0;
	int right=LCD_X;
	int bottom=15;
	int top=0;
	draw_line(left,bottom,right,bottom,FG_COLOUR);
	draw_line(left,top,right,top,FG_COLOUR);
	draw_line(left,top,left,bottom,FG_COLOUR);
	draw_line(right-1,top,right-1,bottom,FG_COLOUR);
	for (int i = 1; i < bottom; i++)
	{
		/* code */
		draw_line(left+1,i,right-2,i,BG_COLOUR);
	}
	sprintf(buff,"S:%.1f",speed);
	draw_string(1,1,buff,FG_COLOUR);

	sprintf(buff,"HP:%d",HP);
	draw_string(28,1,buff,FG_COLOUR);

	sprintf(buff,"F:%d",fuel);
	draw_string(58,1,buff,FG_COLOUR);

	// double time=get_current_time();
	// sprintf(buff,"Time:%.2f",time);
	// draw_string(0,LCD_Y/2,buff,FG_COLOUR);

	

}
void pause_view(void){
	double timer2=get_current_time();
	// bool ispaused=false;
	if (right_pressed && offscreen)
	{
		/* code */
		ispaused=true;
	}
	while(ispaused){
		clear_screen();
		SET_BIT(PORTB,2);
		pausetime=timer2;
	    sprintf(buff,"Time:%.2f",pausetime);
		draw_string(10,20,buff,FG_COLOUR);

		sprintf(buff,"D:%d",distance);
		draw_string(10,11,buff,FG_COLOUR);

		show_screen();
		if (pressed)
		{ 
			ispaused=false;
			CLEAR_BIT(PORTB,2);
		}

	}
}


void draw_road(void){
	int left= (LCD_X/6)*2;
	int right=(LCD_X/6)*4;
	int top=0;
	int bottom=LCD_Y;
	draw_line(left,top,left,bottom,FG_COLOUR);
	draw_line(right,top,right,bottom,FG_COLOUR); 
}

bool is_car_offroad(void){
	int left= (LCD_X/6)*2;
	int right=(LCD_X/6)*4;
	if (car.x>=0 && car.x<= left)
	{
		return true;
	}
	else if (car.x+8>right && car.x<LCD_X)
	{
		return true;
	}
	else{
		return false;
	}
}

void movement(void){
	
	if (left_joy_state && car.x >1 && speed >0)
	{
		/* code */
		car.x-=speed;
		if (is_car_offroad() && speed>3)
		{
			speed=3;
		}
	}
	else if (right_joy_state && car.x<LCD_X-10 && speed>0)
	{
		car.x+=speed;
		if (is_car_offroad() && speed>3)
		{
			speed=3;
		}
	}
	else if (!up_joy_state && !down_joy_state && speed<=1)
	{
		/* code */
		if (is_car_offroad())
		{
			/* code */
			speed+=0.05;
			if (speed>1)
			{
				speed=1;
			}
		}
		else{
			speed+=0.10;
			if (speed>1)
			{
				speed=1;
			}
		}
	}
	else if (up_joy_state && speed>=1 && speed<10)
	{
		/* code */
		if (is_car_offroad())
		{
			/* code */
			speed+=0.1;
			if (speed>=3)
			{
				/* code */
				speed=3;
			}
		}
		else{

			speed+=0.35;
			if (speed>10)
			{
				/* code */
				speed=10;
			}		
		}
	}
	else if (!up_joy_state && !down_joy_state && speed>1)
	{
		/* code */
		if (is_car_offroad())
		{
			/* code */
			speed-=0.10;
			if (speed<=1)
			{
				speed=1;
			}
		}
		else{
			speed-=0.5;
			if (speed<1)
			{
				speed=1;
			}
		}
	}
	
	else if (down_joy_state && speed>0)
	{
		speed-=0.6;
		if (speed<0)
		{
			/* code */
			speed=0;
		}
	}
	
	clear_screen();

}

void distance_travelled(void){
	if (speed>0 && fuel>0)
	{
		/* code */
		distance+=speed;
	}
}

void fuel_consumption(void){
	if (speed>0 && fuel>0)
	{
		/* code */
		fuel-=0.05*speed;
	}
	if (fuel<=0)
	{
		/* code */
		fuel=0;
	}
}

bool collided(sprite_id s1, sprite_id s2){
	int th = round(s1->y);
	int lh = round(s1->x);
	int rh = lh + s1->width - 1;
	int bh = th + s1->height - 1;

	int tz = round(s2->y);
	int lz = round(s2->x);
	int rz = lz + s2->width - 1;
	int bz = tz + s2->height - 1;
	
	if ( tz > bh ) return false;
	if ( th > bz ) return false;
	if ( lh > rz ) return false;
	if ( lz > rh ) return false;
	
	
	return true;
}

void safe_restart(void){
	int left= (LCD_X/6)*2;
	int right=(LCD_X/6)*4;

	int position_x=left+1;
	int position_y=LCD_Y-9;
	// bool collision=false;

	bool colliding=true;
	while(colliding){
		position_x++;
		if (position_x >= right- car.width)
		{
			/* code */
			position_y--;
			position_x=left+1;
		}
		car.x=position_x;
		car.y=position_y;
		colliding=false;
		for (int i = 0; i < obstacles_count; i++)
		{
			/* code */
			if (collided(&car,&obstacles[i]))
			{
				/* code */
				colliding=true;
			}
		}
		for (int v = 0; v < offroad_count; v++)
		{
			/* code */
			if (collided(&car,&tree[v]) || collided(&car,&house[v]))
			{
				/* code */
				colliding=true;
			}
		}
	}

	speed=0;
	fuel=500;
	
}

void check_gameover(void){
	
	if (fuel==0 || collided(&car,&fuelstation) || HP==0 || cross_finish_line)
	{
		/* code */
		game_over=true;
		clear_screen();
		lcd_clear();
		double time=get_current_time();
		if (cross_finish_line)
		{
			draw_string_direct((LCD_X - 6 * CHAR_WIDTH) / 2 - 10, (1 * CHAR_HEIGHT)-3, "WINNER", FG_COLOUR);	
		}
		else{
			draw_string_direct((LCD_X - 6 * CHAR_WIDTH) / 2 - 10, (1 * CHAR_HEIGHT)-3, "GAME OVER", FG_COLOUR);
		}
		sprintf(buff,"D:%d",distance);
		draw_string_direct((LCD_X - 6 * CHAR_WIDTH) / 2 - 23, (2 * CHAR_HEIGHT)-3, buff, FG_COLOUR);
		sprintf(buff,"T:%.2f",time);
		draw_string_direct((LCD_X - 6 * CHAR_WIDTH) / 2+15, (2 * CHAR_HEIGHT)-3,buff, FG_COLOUR);
		draw_string_direct((LCD_X - 6 * CHAR_WIDTH) / 2-10, 3 * CHAR_HEIGHT, "PLAY AGAIN?", FG_COLOUR);
	    draw_string_direct((LCD_X - 6 * CHAR_WIDTH) / 2-10, 4 * CHAR_HEIGHT, "L-BTN->YES", FG_COLOUR);
	    draw_string_direct((LCD_X - 6 * CHAR_WIDTH) / 2-10, 5 * CHAR_HEIGHT, "R-BTN->NO", FG_COLOUR);
	 	
	 	while(!pressed && !right_pressed){

	 	}
	 	if (pressed)
	 	{
	 		/* code */
	 		SET_BIT(PORTB,3);
	 		lcd_clear();
	 		new_game=true;
	 	}
	 	else if (right_pressed)
	 	{
	 		/* code */
	 		lcd_clear();
	 		new_game=false;
	 		draw_string_direct((LCD_X - 6 * CHAR_WIDTH) / 2-10, 3 * CHAR_HEIGHT, "GOODBYE", FG_COLOUR);

	 	}

	}
}


void draw_int(uint8_t x, uint8_t y, int value, colour_t colour) {
	snprintf(buffer, sizeof(buffer), "%d", value);
	draw_string(x, y, buffer, colour);
}

void setup_teensy(void){
	set_clock_speed(CPU_8MHz);
	usb_init();
	lcd_init(50);
	// clear_screen();
	//right button
	CLEAR_BIT(DDRF,5);
	//left button
	CLEAR_BIT(DDRF,6);
	//LEFT JOYSTICK
	CLEAR_BIT(DDRB,1);
	//RIGHT JOYSTICK
	CLEAR_BIT(DDRD,0);
	//UP JOYSTICK
	CLEAR_BIT(DDRD,1);
	//DOWN JOYSTICK
	CLEAR_BIT(DDRB,7);

	//left led
	SET_BIT(DDRB,2);
	//right led
	SET_BIT(DDRB,3);
	
	// SET_BIT(PORTC,7);

	//Setting ADC
	WRITE_BIT(ADMUX, REFS0, 1);
	WRITE_BIT(ADMUX, REFS1, 0);

	//ENABLE ADC
	WRITE_BIT(ADCSRA,ADEN,1);

	//SET PRESCALAR TO 128 HIGHEST DIVISION
	WRITE_BIT(ADCSRA, ADPS0, 1);
    WRITE_BIT(ADCSRA, ADPS1, 1);
    WRITE_BIT(ADCSRA, ADPS2, 1);

    //enable pwm on lcd backlight
    TC4H = 1023 >> 8;
	OCR4C = 1023 & 0xff;
	TCCR4A = BIT(COM4A1) | BIT(PWM4A);
	//lcd led
	SET_BIT(DDRC,7);

	// (c)	Set pre-scale to "no pre-scale" 
	TCCR4B = BIT(CS42) | BIT(CS41) | BIT(CS40);
	//use fast pwm
	TCCR4D = 0;
}


void set_duty_cycle(int duty_cycle) {
	// (a)	Set bits 8 and 9 of Output Compare Register 4A.
	TC4H = duty_cycle >> 8;

	// (b)	Set bits 0..7 of Output Compare Register 4A.
	OCR4A = duty_cycle & 0xff;
}
//blinks when car is off the road
void blinking(int duty_cycle){
	TC4H = 0;
	OCR4A = 0;
	_delay_ms(10);
	TC4H = duty_cycle >> 8;
	OCR4A = duty_cycle & 0xff;
}

void setup_timer(void){
	//	(a) Initialise Timer 1 in normal mode so that it overflows 
	//	with a period of approximately 2.1 seconds.
	//	Hint: use the table you completed in a previous exercise.
	TCCR1A=0;
	TCCR1B=4;


	//	(b) Enable timer overflow for Timer 1.
	TIMSK1=1;

	//	(c) Turn on interrupts.
	sei();
}

void setup_debouncetimer(void){
	//	(a) Initialise Timer 0 in normal mode so that it overflows 
	//	with a period of approximately 0.008 seconds.
	//	Hint: use the table you completed in a previous exercise.
	TCCR0A=0;
	TCCR0B=4;

	//	(b) Enable timer overflow interrupt for Timer 0.
	TIMSK0=1;

	//	(c) Turn on interrupts.
	sei();

}

void setup(void){
	welcome();
	srand(counter);
	rand();
	setup_car();
	setup_tree();
	setup_house();
	setup_depot();
	setup_obstacles();
	setup_finishline();


}

ISR(TIMER1_OVF_vect) {
	if (!ispaused)
	{
		counter ++;
	}
}
//setting up debouncing of all switches using interrupts(8bit timer)
//set a function for left,right,buttons that returns true or false depending on the pressed etc. look at the prevstate and currentstate in ams


ISR(TIMER0_OVF_vect){
	left_button=((left_button<<1) & 0b00000111) | BIT_VALUE(PINF,6);
	right_button=((right_button<<1) & 0b00000111) | BIT_VALUE(PINF,5);
	L_JOYSTICK=((L_JOYSTICK<<1) & 0b00000111) | BIT_VALUE(PINB,1);
	R_Joystick=((R_Joystick<<1) & 0b00000111) | BIT_VALUE(PIND,0);
	U_joystick=((U_joystick<<1) & 0b00000111) | BIT_VALUE(PIND,1);
	D_joystick=((D_joystick<<1) & 0b00000111) | BIT_VALUE(PINB,7);
	C_joystick=((C_joystick<<1) & 0b00000111) | BIT_VALUE(PINB,0);


	//for left button
	if (left_button==0b00000111)
	{
		/* code */
		pressed=1;
	}
	if (left_button==0)
	{
		/* code */
		pressed=0;
	}

	//for right button
	if (right_button==0b00000111)
	{
		/* code */
		right_pressed=1;
	}
	if (right_button==0)
	{
		/* code */
		right_pressed=0;
	}

	//for left joystick
	if (L_JOYSTICK==0b00000111)
	{
		/* code */
		left_joy_state=1;
	}
	if (L_JOYSTICK==0)
	{
		/* code */
		left_joy_state=0;
	}

	//for right joystick
	if (R_Joystick==0b00000111)
	{
		/* code */
		right_joy_state=1;
	}
	if (R_Joystick==0)
	{
		/* code */
		right_joy_state=0;
	}

	//for up joystick
	if (U_joystick==0b00000111)
	{
		/* code */
		up_joy_state=1;
	}
	if (U_joystick==0)
	{
		/* code */
		up_joy_state=0;
	}

	//for down joystick
	if (D_joystick==0b00000111)
	{
		/* code */
		down_joy_state=1;
	}
	if (D_joystick==0)
	{
		/* code */
		down_joy_state=0;
	}

	//for centre joystick
	if (C_joystick==0b00000111)
	{
		/* code */
		centre_joy_state=1;
	}
	if (C_joystick==0)
	{
		/* code */
		centre_joy_state=0;
	}
	
	
}

double get_current_time(){
	double time = ( counter * 65536.0 + TCNT1 ) * 256.0  / 8000000.0;
	return time;
}



void process(void){
	
	long left_adc=adc_read(0);
	set_duty_cycle(1023-left_adc);
	
	movement();
	if (is_car_offroad())
	{
		/* code */
		blinking(1023-left_adc);
	}
	distance_travelled();
	fuel_consumption();
	sprite_draw(&car);
	
	for (int i = 0; i < offroad_count; i++)
	{
		/* code */
		sprite_draw(&tree[i]);
	}
	for (int v = 0; v < offroad_count; v++)
	{
		/* code */
		step_tree(&tree[v]);
	}

	for (int h = 0; h < offroad_count; h++)
	{
		/* code */
		sprite_draw(&house[h]);
	}
	for (int g = 0; g < offroad_count; g++)
	{
		/* code */
		step_house(&house[g]);
	}

	sprite_draw(&fuelstation);
	step_fuelstation(&fuelstation);
	refill();

	for (int i = 0; i < obstacles_count; i++)
	{
		/* code */
		sprite_draw(&obstacles[i]);

	}
	for (int o = 0; o < obstacles_count; o++)
	{
		/* code */
		step_obstacles(&obstacles[o]);
	}
	//collision with scenery
	// safe_restart();
	for (int c = 0; c < offroad_count; c++)
	{
		if (collided(&car,&tree[c])||collided(&car,&house[c])||collided(&car,&obstacles[c]))
		{
			if (HP>0)
			{
				if (collided(&car,&obstacles[c]))
				{
					/* code */
					HP=HP-20;
				}
				else{
					HP=HP-10;	
				}
				if (HP <= 0)
				{
					HP=0;
				}
			}
			safe_restart();
		}
	}
	if (car.y<=LCD_Y-10 && speed>0)
	{
		/* code */
		car.y+=speed*0.3;
	}

	sprite_draw(&finish);
	step_finishline(&finish);

	draw_int(0,0,speed,FG_COLOUR);
	draw_road();
	dashboard();
	pause_view();
	show_screen();
	check_gameover();
	
}

int main()
{
	setup_teensy();
	setup_timer();
	setup_debouncetimer();
	setup();
	while(new_game){
		new_game=false;
		game_over=false;
		HP=100;
		fuel=500;
		speed=0;
		distance=0;
		cross_finish_line=false;
		finish.y=0;
		fuelstation.y=-2;
		for (int i = 0; i < obstacles_count; i++)
		{
			/* code */
			obstacles[i].y -= 11;
		}
		counter=0;
		while(!game_over){
			process();
			_delay_ms(100);
		}
	}
	return 0;
}

