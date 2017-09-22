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

Bullets::Bullets()
{
	live = false;
	x = -1;
	y = -1;
	speed = 0.6;
	speedX = 0;
	speedY = 0;
}

Bullets::~Bullets()
{
}

void Bullets::UpdateBullet(){
	if (live){
		x += speedX;
		y += speedY;
	}
	if (x > widthSquare)
		live = false;
	if (y > heightSquare)
		live = false;
	if (y < 0)
		live = false;
}
void Bullets::DrawBullet(){
	if (live){
		al_draw_filled_circle(x * square_l, y * square_l, 2, al_map_rgb(0, 250, 0));
	}
}
void Bullets::setSpeedX(float x){
	speedX = x;
}
void Bullets::setSpeedY(float x){
	speedY = x;
}
void Bullets::setLive(bool s){
	live = s;
	if (s == false){
		x = -1;
		y = -1;
		speed = 0.6;
		speedX = 0;
		speedY = 0;
	}
}
void Bullets::setX(float z){
	x = z;
}
void Bullets::setY(float z){
	y = z;
}

bool Bullets::isLive(){
	if (live)
		return true;
	else
		return false;
}

float Bullets::getSpeed(){
	return speed;
}
float Bullets::getSpeedX(){
	return speedX;
}
float Bullets::getSpeedY(){
	return speedY;
}
float Bullets::getX(){
	return x;
}
float Bullets::getY(){
	return y;
}