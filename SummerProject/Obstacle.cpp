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


Obstacle::Obstacle()
{
}

Obstacle::Obstacle(float pozx, float pozy, ALLEGRO_BITMAP *img){
	x = pozx;
	y = pozy;
	boundx = 4;
	boundy = 4;
	image = img;
}

Obstacle::Obstacle(float pozx, float pozy){
	x = pozx;
	y = pozy;
	boundx = 4;
	boundy = 4;
}

Obstacle::~Obstacle()
{
}

void Obstacle::Collide(Bullets &bullet){
	if (bullet.getX() >= x && bullet.getX() <= x + boundx && bullet.getY() >= y && bullet.getY() <= y + boundy){
		bullet.setLive(false);
	}
}

void Obstacle::DrawObstacle(){
	//al_draw_filled_rectangle(x * square_l, y * square_l, square_l * (x + boundx), square_l * (y + boundy), al_map_rgb(137, 10, 137));
	al_draw_bitmap(image, x * square_l, y * square_l, 0);
}