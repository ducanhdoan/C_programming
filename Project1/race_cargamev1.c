//assignment 1, racing car game

#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <cab202_graphics.h>
#include <cab202_sprites.h>
#include <cab202_timers.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

//Global variables
int speed = 0;
int fuel=5000;
int HP=100;
int Distance=0;
bool game_over=false;
double start_time=0.0;
bool depot_exists=false;
double pause_death=9999999;
bool top_up= true;
bool cross_finish_line= false;
bool new_game=true;
//fuelstation left or right
int x=0;

//part B 
double zombie_speed=0.05;




sprite_id car;

sprite_id house[3];
int house_count=3;

sprite_id rock[3];
int rock_count=3;

sprite_id tree[3];
int tree_count=3;

sprite_id fuelstation;
sprite_id finish;

sprite_id message;
sprite_id victory;


#define MAX_ZOMBIES (100)
// sprite_id * zombie;
sprite_id zombie[MAX_ZOMBIES];
int zombie_count=7;


char * house_image="---------"
			 	   "|     _ |"
				   "|    [ ]|"
				   "|    [ ]|"
				   "---------";  

char * rock_image="++++++"
				  "+    +"
				  "+    +"
				  "++++++";

char * tree_image="   ##   "
				  "   @@   "
				  " @@@@@@ "
				  "@@@@@@@@"
			 	  "   ||   "
			      "   ||   ";

char * fuelstation_image="----------"
						 "|[______]|"
						 "|GAS[   ]|"
						 "|REFILL[]|"
						 "----------";


char * car_image="||======||"
				 "   [  ]   "
				 "   [  ]   "
				 "   |[]|   "
				 "||=||||=||" ;

char * finish_img="@";


char * lose_img="L        OOOOO  SSSSS  EEEEE"
				"L        O   O  S      E    "
				"L        O   O  SSSSS  EEEEE"
				"L        O   O      S  E    "
				"LLLLLLL  OOOOO  SSSSS  EEEEE";


char * vic_img=   "W            W  @   NN    N"
				  " W          W   @   N N   N"
				  "  W   WW   W    @   N  N  N"
				  "   W W  W W     @   N   N N"
				  "    W    W      @   N    NN";





char * zombie_img=" +@@+ "
			      "  ||  "
			      "|-OO-|"
			      "  MM  ";

//Global functions
void welcome(void);
void draw_border(void);
void dashboard(void);
void setup_game(void);
void process(void);
void draw_road(void);
bool is_car_offroad(void);
void movement(void);
void distance_travelled(void);
void refuelling(void);
bool overlap(sprite_id scenery1,sprite_id scenery2);


int main(void)
{
	srand(time(NULL));
	setup_screen();
	welcome();
	setup_game();
	while(new_game){
		HP = 100;
		fuel = 5000;
		Distance=0;
		top_up=true;
		game_over=false;
		new_game = false;
		if (cross_finish_line) {
			finish->y = 2;
			speed = 0;
		}
		cross_finish_line=false;
		fuelstation->y=2;
		speed=0;

		start_time=get_current_time();
		while(!game_over){
			process();
			timer_pause(20);
		}
	}
	
	
	return 0;
}

//splash screen
void welcome(void){
	int w=screen_width();
	int h= screen_height();

	draw_string(w/4,h/4,"Race To Zombie Mountain Game");
	draw_string(w/4,(h/4)+2,"By Kevin Gunawan, n9812482");
	draw_string(w/4,(h/4)+4,"How to Play: ");
	draw_string(w/4,(h/4)+5,"Press a to Move LEFT");
	draw_string(w/4,(h/4)+6,"Press d to Move RIGHT");
	draw_string(w/4,(h/4)+7,"Press w to SPEED UP");
	draw_string(w/4,(h/4)+8,"Press s to SLOW DOWN");
	draw_string(w/4,(h/4)+9,"Press p to pause/resume");

	draw_string(w/4,(h/4)+12,"Press any key to start");


	show_screen();
	wait_char();
	clear_screen();

}

void draw_border(void){
	int left=0;
	int top=0;
	int right=screen_width()-1;
	int bottom=screen_height()-1;
	draw_line(left,top,right,top,'@');
	draw_line(right,top,right,bottom,'@');
	draw_line(left,bottom,right,bottom,'@');
	draw_line(left,top,left,bottom,'@');

	dashboard();
	draw_road();

}

void draw_road(void){
	int w=screen_width();
	int h=screen_height();
	int road_l=(w-2)/4;
	int road_top=1;
	int road_r=((w-2)/4)*3;
	int road_b= h-2;

	draw_line(road_l,road_top+10,road_l,road_b,'|');
	draw_line(road_r,road_top+10,road_r,road_b,'|');

}

void dashboard(void){
	int dash_l= 1;
	int dash_top=1;
	int dash_r= screen_width()-2;
	int dash_b=10;
	double time= get_current_time()-start_time;
	for (int i = dash_top; i < dash_b; i++)
	{
		draw_line(dash_l,i,dash_r,i,'/');
	}

	draw_string(3,4,"Speed:   /10");
	draw_int(10,4,speed);

	draw_string( 20,4,"HP:     /100");
	draw_int(24,4,HP);

	draw_string(40,4,"Fuel:      /5000");
	draw_int(46,4,fuel);

	draw_formatted(3,8,"Elapsed Time: %.2f",time);

	draw_string(40,8,"Distance travelled:");
	draw_int(60,8,Distance);


}

bool is_car_offroad(void){
	int x= round(sprite_x(car));
	int w=screen_width();
	int car_w=sprite_width(car);
	int road_r=((w-2)/4)*3;
	if (x>2 && x<=(w-2)/4)
	{
		return true;
	}
	else if (x+car_w>road_r && x<w-12)
	{
		return true;
	}
	else{
		return false;
	}
}

void movement(void){
	int key;

	key=get_char();

	// pause();
	if (key=='a' && sprite_x(car)>2 && speed>0)
	{
		sprite_move(car,-1,0);
		if (is_car_offroad())
		{
			
			speed=3;
		}
	}
	else if (key=='w' && speed < 10)
	{
		speed++;
		if(is_car_offroad() && speed>3)
		{
			speed=3;
		}
	}

	else if (key=='s' && speed > 0)
	{
		speed--;
	}

	else if (key=='d' && sprite_x(car)<screen_width()-12 && speed >0)
	{
		sprite_move(car,+1,0);
		if(is_car_offroad())
		{
			
			speed=3;
		}
	}
//pause function
	else if (key=='p')
	{
		key=wait_char();
		if (key=='p')
		{
			return;
		}
	}

	else if (key=='q')
	{
		game_over=true;
		return;
	}


	clear_screen();
}

void fuel_consumption(void){
	if(speed>0 && fuel >0){
		fuel-= 0.1*speed;
	}
	else if (fuel<=0)
	{
		fuel=0;
	}
}

void distance_travelled(void){
	if (speed>0 && fuel>0)
	{
		Distance+=speed;
	}

}

//scenery part
sprite_id create_tree(void){
	int w=screen_width();
	int h=screen_height();
	int road_l=(w-2)/4;
	int top=11;
	int bottom=h-2;
	int random_treex=1+(rand()%(road_l-19));
	int random_treey=top+(rand()%(bottom-top));

	sprite_id tree=sprite_create(random_treex,random_treey,8,6,tree_image);
	sprite_draw(tree);

	return tree;
}

void step_tree(sprite_id tree){
	int w=screen_width();
	int road_l=(w-2)/4;
	sprite_step(tree);
	double dx=sprite_dx(tree);
	double dy=sprite_dy(tree);
	dy=0.1*speed;
	sprite_turn_to(tree,dx,dy);
	if (sprite_y(tree) > screen_height()) {
		sprite_move_to(tree,1+(rand()%(road_l-19)),2);
	}

}

sprite_id create_house(void){
	int w=screen_width();
	int h=screen_height();
	int road_r=((w-2)/4)*3;
	int top=11;
	int bottom=h-2;
	int random_housex=road_r+11+(rand()%(w-road_r-20));
	int random_housey=top+(rand()%(bottom-top));

	sprite_id house=sprite_create(random_housex,random_housey,9,5,house_image);
	sprite_draw(house);

	return house;

}

void step_house(sprite_id house){
	int w=screen_width();
	int road_r=((w-2)/4)*3;
	int random_housex=road_r+11+(rand()%(w-road_r-21));
	sprite_step(house);
	double dx=sprite_dx(house);
	double dy=sprite_dy(house);
	dy=0.1*speed;
	sprite_turn_to(house,dx,dy);

	if (sprite_y(house)>screen_height())
	{
		sprite_move_to(house,random_housex,2);
	}
}

sprite_id create_rock(void){
	int w=screen_width();
	int h=screen_height();
	int road_l=(w-2)/4;
	int road_r=((w-2)/4)*3;
	int top=11;
	int bottom=h-11;

	int random_rockx=road_l+1+(rand()%(road_r-road_l-7));
	int random_rocky=top+(rand()%(bottom-top));

	sprite_id rock=sprite_create(random_rockx,random_rocky,6,4,rock_image);
	sprite_draw(rock);

	return rock;
}

void step_rock(sprite_id rock){
	int w=screen_width();
	int road_l=(w-2)/4;
	int road_r=((w-2)/4)*3;
	sprite_step(rock);
	double dy=sprite_dy(rock);
	double dx=sprite_dx(rock);
	dy=0.1*speed;
	sprite_turn_to(rock,dx,dy);

	if (sprite_y(rock) > screen_height()) {
		sprite_move_to(rock,road_l+1+(rand()%(road_r-road_l-7)),2);
	}

}

bool overlap(sprite_id scenery1,sprite_id scenery2){
	int x1=sprite_x(scenery1);
	int y1=sprite_y(scenery1);
	int x1r=x1+sprite_width(scenery1);
	int y1b=y1+sprite_height(scenery1);

	int x2=sprite_x(scenery2);
	int y2=sprite_y(scenery2);
	int x2r=x2+sprite_width(scenery2);
	int y2b=y2+sprite_height(scenery2);

	if (y1b<y2)
	{
		return false;
	}
	if (y1>y2b)
	{
		return false;
	}
	if (x1r<x2)
	{
		return false;
	}
	if (x1>x2r)
	{
		return false;
	}

	return true;


}

//fuel station part
sprite_id create_depot(void){
	int w=screen_width();
	int road_l=((w-2)/4)-10;
	int road_r=(((w-2)/4)*3)+1;
	int position=2;
	int random[2]={road_l,road_r};

	int x=rand()%2;
	int position_x=random[x];

	sprite_id fuelstation=sprite_create(position_x,position,10,5,fuelstation_image);
	sprite_draw(fuelstation);

	return fuelstation;
}

void step_depot(sprite_id fuelstation){
	int w=screen_width();
	int road_l=((w-2)/4)-10;
	int road_r=(((w-2)/4)*3)+1;
	int random[2]={road_l,road_r};
	int position_x=random[x];
	if ((fuel>=2000 && fuel<=3000)||(fuel<1000))
	{
		sprite_step(fuelstation);
		double dy=sprite_dy(fuelstation);
		double dx=sprite_dx(fuelstation);
		dy=0.1*speed;
		sprite_turn_to(fuelstation,dx,dy);

		if (sprite_y(fuelstation)>screen_height())
		{
			sprite_move_to(fuelstation,position_x,2);
			x += 1;
			x %= 2;
		}
	}

}

void refuelling(void){
	int depot=round(sprite_x(fuelstation));
	int position=round(sprite_y(fuelstation));
	int x=sprite_x(car);
	int y=sprite_y(car);
	int xf=sprite_x(fuelstation);
	double stop_watch=get_current_time()-start_time;

	if (stop_watch>=pause_death+3 && top_up==false)
	{
		if (x>=depot+10 && x<=depot+10+1)
		{
			sprite_move_to(car,x+2,y);
			sprite_move_to(fuelstation,xf,2);
			fuel=5000;
			top_up=true;
		}
		else if (x+10<=depot && x+10>=depot-1)
		{
			sprite_move_to(car,x-2,y);
			sprite_move_to(fuelstation,xf,2);
			fuel=5000;
			top_up=true;
		}
	}

	if (((x>=depot+10 && x<=depot+10+1) && top_up) ||((x+10<=depot && x+10>=depot-1) && top_up))
	{
		if (y==position)
		{
			speed=0;
			pause_death=get_current_time()-start_time;
			top_up=false;
			
		}

	}
}

void interval(int fuel){
	int x= rand()%2;
	if (fuel>=2000 && fuel<=3000)
	{

		if (x==1 || depot_exists)
		{
			sprite_draw(fuelstation);
			depot_exists=true;

		}
	}
	else if (fuel<1000)
	{
		sprite_draw(fuelstation);
	}
	else {
		depot_exists=false;
	}
}
//finishing line part
sprite_id create_fin(void){
	int w=screen_width();
	int road_l=(w-2)/4;
	int road_r=((w-2)/4)*3;
	finish=sprite_create(road_l,2,road_r-road_l,1,finish_img);
	
	return finish;
}

void step_finish(sprite_id finish){
	if (Distance >= 15000 && speed >0)
	{
		sprite_step(finish);
		double dy=sprite_dy(finish);
		double dx=sprite_dx(finish);
		dy=0.1*speed;
		sprite_turn_to(finish,dx,dy);
	}

}


void finish_line(void){
	int x1=sprite_x(finish);
	int y=sprite_y(finish);
	int x2= sprite_x(finish)+sprite_width(finish)-1;
	if (Distance >= 15000)
	{
		draw_line(x1,y,x2,y,'=');
	}
	if (sprite_y(car)<= sprite_y(finish))
	{
		cross_finish_line=true;
	}
}

//collision with obstacles part;
bool collision(sprite_id car2,sprite_id rock1){
	int lc=round(sprite_x(car2));
	int tc=round(sprite_y(car2));
	int rc=lc+sprite_width(car2)-1;
	int bc=tc+sprite_height(car2)-1;

	int lr=sprite_x(rock1);
	int tr=sprite_y(rock1);
	int rr=lr+sprite_width(rock1);
	int br=tr+sprite_height(rock1);

	if (br < tc)
	{
		return false;
	}
	if (tr>bc)
	{
		return false;
	}
	if (rr<lc)
	{
		return false;
	}
	if (lr>rc)
	{
		return false;
	}

	return true;
}

void move_away(sprite_id car){
	int w=screen_width();
	int h=screen_height();
	int road_l=(w-2)/4;
	int road_r=((w-2)/4)*3-11;
	int rand_x=road_l+(rand()%(road_r-road_l));
	sprite_move_to(car,rand_x,h-6);
	speed=0;
	fuel=5000;

}

void crashed(void){
	bool crash=false;
	for (int i = 0; i < rock_count; i++)
	{
		if (collision(car,rock[i]))
		{
			if (HP>0)
			{
				HP=HP-20;
				if (HP <= 0)
				{
					HP=0;
				}
			}
			crash=true;
			break;
		}
	}
	for (int y = 0; y < house_count; y++)
	{
		if (collision(car,house[y]))
		{
			if (HP>0)
			{
				HP=HP-10;
				if (HP <= 0)
				{
					HP=0;
				}
			}
			crash=true;
			break;
		}
	}
	for (int x = 0; x < tree_count; x++)
	{
		if (collision(car,tree[x]))
		{
			if (HP>0)
			{
				HP=HP-10;
				if (HP <= 0)
				{
					HP=0;
				}
			}
			crash=true;
			break;
		}
	}

	if (crash)
	{
		for (int i = 0; i < rock_count; i++)
		{
			while(collision(car,rock[i]) || collision(car,house[i]) || collision(car,tree[i])){
				move_away(car);
				crash=false;
			}
		}	
	}
}

//check game_over
sprite_id gameover_msg(void){
	int w=screen_width();
	int h=screen_height();
	int msg_height=5;
	int msg_width=strlen(lose_img)/msg_height;
	sprite_id message=sprite_create((w-msg_width)/2,(h-msg_height)/2,msg_width,msg_height,lose_img);
	sprite_draw(message);

	return message;
}

sprite_id victory_msg(void){
	int w=screen_width();
	int h=screen_height();
	int vic_height=5;
	int vic_width=strlen(vic_img)/vic_height;
	sprite_id victory=sprite_create((w-vic_width)/2,(h-vic_height)/2,vic_width,vic_height,vic_img);
	sprite_draw(victory);

	return victory;
}

void msg_screen(void){
	int w= screen_width();
	int h=screen_height();
	double score=get_current_time()-start_time;
	draw_string(w/2-5,h-15,"You have travelled: ");
	draw_int((w/2-5)+20,h-15,Distance);
	draw_formatted((w/2-5),h-12,"Your elapsed time is:%.2f",score);
	draw_string((w/2-5),h-10,"Do you wish to play one more time?(y/n): ");
}

void response_wait(void){
	int response;
	timer_pause(1000);

	response=wait_char();
	if (response=='n')
	{
		game_over=true;
		new_game=false;

	}
	else if (response=='y')
	{
		game_over=true;
		new_game=true;
	}
}


void check_gameover(void){
	if (collision(car,fuelstation))
	{
		HP=0;
	}
	if (HP==0 || fuel == 0)
	{
		game_over=true;
		clear_screen();
		message=gameover_msg();
		msg_screen();
		show_screen();
		response_wait();

	}
	else if (cross_finish_line)
	{
		game_over=true;
		clear_screen();
		victory=victory_msg();
		msg_screen();
		show_screen();
		response_wait();

	}


}

//extensions Part B

sprite_id create_zombie(void){
	int w=screen_width();
	int h=screen_height();
	int road_l=1;
	int road_r=w-7;
	int top=1;
	int bottom=h-11;
	int zombie_x=road_l+(rand()%(road_r-road_l));
	int zombie_y=top+(rand()%(bottom-top));

	sprite_id zombie=sprite_create(zombie_x,zombie_y,6,4,zombie_img);
	sprite_draw(zombie);

	double zdx=zombie_speed;
	double zdy=zombie_speed;
	sprite_turn_to(zombie,zdx,zdy);

	return zombie;

}

void step_zombie(sprite_id zombie,sprite_id rock,sprite_id house, sprite_id tree,sprite_id fuelstation){
	int w=screen_width();
	int h=screen_height();
	int old_zx=round(sprite_x(zombie));
	double zdx=sprite_dx(zombie);
	double zdy=sprite_dy(zombie);

	int zy=round(sprite_y(zombie));
	int zx= round(sprite_x(zombie));
	zdy=zombie_speed+(0.1*speed);

	if (zy>h)
	{
		sprite_move_to(zombie,old_zx,2);
		zdx=-zdx;
	}

	if (zx<1 || zx>w-7)
	{
		zdx=-zdx;
	}

	if (collision(zombie,rock)||collision(zombie,house)||collision(zombie,tree)|| collision(zombie,fuelstation))
	{
		zdy=-zdy;
		sprite_back(zombie);
	}

	sprite_turn_to(zombie,zdx,zdy);
	sprite_step(zombie);


}
//part B collision

void eat(sprite_id car){
	int w=screen_width();
	int h=screen_height();
	int road_l=(w-2)/4;
	int road_r=((w-2)/4)*3-11;
	int rand_x=road_l+(rand()%(road_r-road_l));
	sprite_move_to(car,rand_x,h-6);
	speed=0;
	fuel-=50;

}

void zombie_eats(void){
	bool eaten=false;
	for (int z = 0; z < zombie_count; z++)
	{
		if (collision(car,zombie[z]))
		{
			if (HP>0)
			{
				HP=HP-2;
				if (HP <= 0)
				{
					HP=0;
				}
			}
			eaten=true;
			break;
		}
	}

	if (eaten)
	{
		for (int z = 0; z < zombie_count; z++)
		{
			for (int i = 0; i < rock_count; i++)
			{
				while(collision(car,rock[i]) || collision(car,house[i]) || collision(car,tree[i]) || collision(car,zombie[z])){
					eat(car);
					sprite_move_to(zombie[z],sprite_x(zombie[z]),2);
					eaten=false;
				}
			}
		}
			
	}
}


void setup_game(void){
	int w=screen_width();
	int h=screen_height();
	car=sprite_create((w-12)/2,h-6,10,5,car_image);

	sprite_draw(car);
	
	for (int i = 0; i < house_count-2; i++)
	{	
		do{
			house[i]=create_house();
			house[i+1]=create_house();
			house[i+2]=create_house();
		}while(overlap(house[i],house[i+1])|| overlap(house[i],house[i+2]) || overlap(house[i+1],house[i+2]));
	}

	for (int t = 0; t < tree_count-2; t++)
	{
		do{
			tree[t]=create_tree();
			tree[t+1]=create_tree();
			tree[t+2]=create_tree();
		}while(overlap(tree[t],tree[t+1]) || overlap(tree[t],tree[t+2]) || overlap(tree[t+1],tree[t+2]));
	}

	for (int r = 0; r < rock_count-2; r++)
	{
		do
		{
			rock[r]=create_rock();
			rock[r+1]=create_rock();
			rock[r+2]=create_rock();
		}while(overlap(rock[r],rock[r+1]) || overlap(rock[r],rock[r+2]) || overlap(rock[r+1],rock[r+2]));
	}
	//Part B
	for (int i = 0; i < zombie_count; i++)
	{
		zombie[i]=create_zombie();
	}
	fuelstation=create_depot();
	finish=create_fin();
	show_screen();
}

void process(void){
	movement();
	fuel_consumption();
	distance_travelled();

	for (int t = 0; t < tree_count; t++)
	{
		step_tree(tree[t]);
	}
	for (int h = 0; h < house_count; h++)
	{
		step_house(house[h]);
	}
	for (int i = 0; i < rock_count; i++)
	{
		step_rock(rock[i]);
	}
	//Part B
	for (int v = 0; v < zombie_count; v++)
	{
		for (int i = 0; i < rock_count; i++)
		{
			step_zombie(zombie[v],rock[i],house[i],tree[i],fuelstation);
		}
	}
	step_depot(fuelstation);
	step_finish(finish);
	
	refuelling();
	sprite_draw(car);
	for (int i = 0; i < house_count; ++i)
	{
		
		sprite_draw(house[i]);
	}
	for (int j = 0; j < tree_count; j++)
	{
		
		sprite_draw(tree[j]);
	}
	for (int x = 0; x < rock_count; x++)
	{
		sprite_draw(rock[x]);
	}
	//PartB
	for (int z = 0; z <zombie_count ; z++)
	{
		sprite_draw(zombie[z]);
	}
	// fuel depot unexpected interval
	interval(fuel);
	finish_line();
	draw_border();
	crashed();
	zombie_eats();
	show_screen();
	check_gameover();
}