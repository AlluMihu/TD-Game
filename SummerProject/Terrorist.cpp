#include <allegro5\allegro.h>
#include <allegro5\allegro_acodec.h>
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>

#include <cmath>
#include <iostream>
#include <fstream>

#include "Player.h"
#include "globals.h"
#include "Background.h"
#include "Bullets.h"
#include "Enemy.h"
#include "Terrorist.h"
#include "Obstacle.h"


Terrorist::Terrorist(){	
	live = false;
}

Terrorist::Terrorist(float x1, float y1, ALLEGRO_BITMAP *img1, ALLEGRO_BITMAP *img2, ALLEGRO_BITMAP *img3){
	speed = 0.05;
	boundx = 2.2;
	boundy = 2.5;
	live = false;
	x = x1;
	y = y1;

	image1 = img1;
	image2 = img2;
	image3 = img3;
}

Terrorist::~Terrorist()
{
}

void Terrorist::UpdateEnemy(){
	if (x < 7.9)
		live = false;
	x -= speed;
}
void Terrorist::DrawEnemy(int time){
//	al_draw_filled_rectangle(x * square_l, y * square_l, square_l * (x + boundx), square_l * (y + boundy), al_map_rgb(137, 10, 10));
	if (time % 24 < 8)
		al_draw_bitmap(image1, x * square_l, y * square_l, 0);
	if (time % 24 >= 8 && time % 24 < 16)
		al_draw_bitmap(image2, x * square_l, y * square_l, 0);
	if (time % 24 >= 16 && time % 24 <= 23)
		al_draw_bitmap(image3, x * square_l, y * square_l, 0);
}
void Terrorist::Die(Bullets &bullet){
	if (bullet.getX() >= x && bullet.getX() <= x + boundx && bullet.getY() >= y && bullet.getY() <= y + boundy){
		bullet.setLive(false);
		live = false;
	}
}

void Terrorist::setLive(bool x){
	live = x;
}
bool Terrorist::isLive(){
	return live;
}
bool Terrorist::endOfTheRoad(){
	if (x < 7.9){
		return 1;
	}
	return 0;
}